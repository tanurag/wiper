This project is developed in QT.

Basically this project helps to delete files from hard drive permanently by rewriting the mapped lba's with zero
and then deleting the files.

By this way we make sure file was deleted properly.

<b>Introduction</b>
    There are ways through which data is deleted when we delete a file.
    Trim: Most of the current drives (SSD,nvme) support trim command , which basically tells SSD firmware to mark the lba's for deletion and whenever somebody tries to access those lba return 0. 
    Non Trim Drive: In this kind of drives operating system simply drops the inode mapping to lba and deletes related inode from inode table. but data is still present in the mapped lba's as they were not deleted.
    
    This program simlpy gives you mapping of LBA's and when you delete , it goes to particular lba's and writes '0' and then deletes the file. This way we are sure . We have completely deleted the file. So other program can not retrieve the data.
    
    
