/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "fileinfo.h"

FileInfo::FileInfo(std::string filename)
{
    unsigned int i;
    file_ext_t ext;
    linkname[32] = { 0, };
    fd = -1;
    this->filename = filename;
    fd = open(filename.c_str(), O_RDONLY|O_LARGEFILE);
    if (fd < 0) {
        Helper::printError("File Opening Error Occured");
        exit(-1);
    }
    fsync(fd);
    if (fstat64(fd, &st) < 0) {
        Helper::printError("File Opening Error occured");
        goto out;
    }
    stat_bdev();
    total_blks = (st.st_size + st.st_blksize - 1) / st.st_blksize;

    blknum = 0;
    if (ioctl(fd, FIBMAP, &blknum) < 0) {
        Helper::printError("ioctl(FIBMAP)");
        goto out;
    }
    ext.f_pos = 0;
    ext.start_blk = blknum;
    ext.end_blk = blknum;
    ext.blk_count = 1;
    for (i = 1; i < total_blks; i++) {
        blknum = i;
        if (ioctl(fd, FIBMAP, &blknum) < 0) {
            Helper::printError("ioctl(FIBMAP)");
            goto out;
        }
        if ((blknum == 0 && blknum == ext.end_blk) || (ext.end_blk + 1) == blknum) {
            ext.end_blk = blknum;
            ext.blk_count++;
        } else {
            blkList.push_back(ext);
            ext.f_pos = i * st.st_blksize;
            ext.start_blk = blknum;
            ext.end_blk = blknum;
            ext.blk_count = 1;
        }
    }
   blkList.push_back(ext);
out:
        close(fd);
}

void FileInfo::stat_bdev()
{
    char devname[32] = { 0, };
    char linkname[32] = { 0, };
    int fd;
    sprintf(devname, "/dev/block/%d:%d", major(st.st_dev), minor(st.st_dev));
    fd = open(devname, O_RDONLY);
    if (fd < 0)
        return;
    if (fstat(fd, &bdev_stat) < 0)
        goto out;
    if (S_ISBLK(bdev_stat.st_mode)) {
        if (ioctl(fd, HDIO_GETGEO, &geom) < 0)
           start_lba = 0;
        else
           start_lba = geom.start;
    }
    if (readlink(devname, linkname, sizeof(linkname)) < 0)
        goto out;

out:
    close(fd);
}
