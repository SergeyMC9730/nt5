char *__boot_install_strings[64] = {
    // this giant string is going to be concatenated on compile time
    // required for codepoints to load

    /* 0 */ "QWERTYUIOPASDFGHJKLZXCVBNM" // english alphabet with all upper case characters
            "qwertyuiopasdfghjklzxcvbnmzxcvbnm" // english alphabet with all lower case characters
            "[]{}()" // brackets
            "ЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ" // cyrillic alphabet with all upper case characters
            "ёйцукенгшщзхъфывапролджэячсмитьбю" // cyrillic alphabet with all lower case chararcters
            ",.;!?:" // punctuation      
            "/\\|" // slashes
            "1234567890" // numbers
            "<>-=+~*^%№" // math signs
            "\"'`" // quotation marks
            "@#$&_" // random characters 
            "═ • │ ┤ ╡ ╢ ╖ ╕ ╣ ║ ╗ ╝ ╜ ╛ ┐ └ ┴ ┬ ├ ─ ┼ ╞ ╟ ╚ ╔ ╩ ╦ ╠ ═ ╬ ╧ ╨ ╤ ╥ ╙ ╘ ╒ ╓ ╫ ╪ ┘ ┌ █ ▄ ▌ ▐ ▀ ", // lines
    
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
    /* 35*/ "Please enter path to Windows XP installation files.\n\n"
            
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

    /* 50*/ "│Copying: %s"
};