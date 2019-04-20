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
#ifndef FILEINFO_H
#define FILEINFO_H

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/sysmacros.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <libgen.h>
#include <linux/hdreg.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <string>
#include <vector>
#include <helper.h>


typedef struct file_ext {
    __u32 f_pos;
    __u32 start_blk;
    __u32 end_blk;
    __u32 blk_count;
}file_ext_t;


class FileInfo
{

public:
    std::vector<file_ext_t> *blkList;
    std::string filename;
    struct stat64 st;
    struct file_ext ext;
    struct stat bdev_stat;
    struct hd_geometry geom;
    __u32 start_lba;
    __u32 blknum;
    int total_blks;
    int fd;
    char linkname[32];
    FileInfo(std::string filename);
    ~FileInfo();
    void stat_bdev();

};

#endif // FILEINFO_H
