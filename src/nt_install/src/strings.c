/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  SergeyMC9730

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact SergeyMC9730 -- @dogotrigger in Discord
*/

char *__boot_install_strings[64] = {
    /* 0*/ "",
    
    /* 1 */ "NT Setup",

    /* 2 */ "═",

    /* 3 */ "FPS : %.2f",

    /* 4 */ "Press F6 if you need to install a third party SCSI or RAID driver...",
    
    /* 5 */ "Press F2 to run Automated System Recovery (ASR)...",
    
    /* 6 */ "Setup is starting NT",
    
    /* 7 */ " NT Professional Setup",
    
    /* 8 */" Welcome to Setup.",
    
    /* 9 */ "This portion of the Setup program prepares Michaelsoft(R)",
    
    /* 10*/ "NT XP to run on your computer.",
    
    /* 11*/ "\u2022  To set up NT XP now, press ENTER.",
    
    /* 12*/ "\u2022  To repair an NT XP installation using Recovery",
    
    /* 13*/ "   Console, press R.",
    
    /* 14*/ "\u2022  To quit Setup without installation NT XP, press F3.",
    
    /* 15*/ "ENTER=Continue  R=Repair  F3=Quit",
    
    /* 16*/ " NT XP License Agreement",
    
    /* 17*/ "ntresources/license.txt",
    
    /* 18*/ "F8=I agree  ESC=I do not agree",
    
    // this giant string is going to be concatenated on compile time
    /* 19 */ "The following list shows the existing partitions"
             " and\nunparitioned space on this computer."
             "\n\nUse the UP and DOWN ARROW keys to select an item in the list.\n\n"
             "   \u2022 To Setup NT XP on the selected item, press ENTER.\n\n"
             "   \u2022 To create a parition in the unpartitioned space, press C.\n\n"
             "   \u2022 To delete the selected partition, press D.",

    /* 20*/ "%d MB Disk %d at Id %d on bus %d on atapi [MBR]",

    /* 21*/ "Unpartitioned space",

    /* 22*/ "%d MB",

    /* 23*/ "ENTER=Install  C=Create Partition  F3=Quit",

    /* 24*/ "ENTER=Install  D=Delete Partition  F3=Quit",

    /* 25*/ "Please wait until Setup formats the partition",

    /* 26*/ "C:  Partition1 [New (Raw)]",

    /* 27*/ "%d MB (%d free)",

    /* 28*/ "on %d MB Disk %d at Id %d on bus %d on atapi [MBR].",

    /* 29*/ "A new partition for NT XP has been created on\n\n%s.\n\nThis partition must now be formatted.\n\nFrom the list below, select a file system for the new partition.\nUse the UP and DOWN ARROW keys to select the file system you want,\nand then press ENTER.\n\nIf you want to select a different partition for NT XP,\npress ESC.",

    /* 30*/ "Format the partition using the NTFS file system (Quick)",

    /* 31*/ "Format the partition using the FAT file system (Quick) ",

    /* 32*/ "Format the partition using the NTFS file system        ",

    /* 33*/ "Format the partition using the FAT file system         ",

    /* 34*/ "ENTER=Continue  ESC=Cancel",

    // this giant string is going to be concatenated on compile time
    /* 35*/ "Please enter path to Windows XP installation files.\n"
            "You can also mount a CD drive with XP and Setup\n"
            "would try to detect it.\n\n"
            
            "They are required for getting text and image\n"
            "data when booting into graphical environment.\n\n"
            
            "  * Linux Example: /media/user/GRTMPVOL_RU/i386\n"
            "  * Windows Example: D:\\i386",

    /* 36*/ "Entered path does not exist!",

    /* 37*/ "F9 Info:\n",

    /* 38*/ " * C%zu - %s\n",

    /* 39*/ "busy",

    /* 40*/ "free",

    /* 41*/ "Cannot load SCSI and RAID drivers: Not Implemented",

    /* 42*/ "Cannot load ASR: Not Implemented",

    /* 43*/ "Cannot load Recovery Console: Not Implemented",

    /* 44*/ " Setup is formating...",

    /* 45*/ "Cannot load Create Partition routine: Not Implemented",

    /* 46*/ "Please wait while Setup copies files",

    /* 47*/ "to the Windows installation folders.",

    /* 48*/ "This might take several minutes to complete.",

    /* 49*/ " Setup is copying files...",

    /* 50*/ "│Copying: %s",

    /* 51*/ "Please wait while Setup initializes your NT XP configuration.",

    /* 52*/ "This portion of Setup has completed successfully.\n\n"

            "If there is a floppy disk in drive A:, remove it.\n\n"

            "To restart your computer, press ENTER.\n"
            "When your computer restarts, Setup will continue.",

    /* 53*/ "Your computer will reboot in %d seconds...",

    /* 54*/ "ENTER=Restart Computer",

    /* 55*/ "Restarting computer...",

    /* 56*/ "Creating information file config.json..."
};