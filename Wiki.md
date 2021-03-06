[[project_screenshots]]

[TOC]

## 1. Summary

Simply-Scripted Backup (SS-Backup for short) is a lightweight utility for performing backups. It does a straight copy of files and folders (when the source is newer than the backup) and optionally stores the old backup file versions under a time-stamped folder. It can also clean the backup by deleting (or optionally moving to a time-stamped folder) files and folders that no longer appear in the source.

As an additional feature, the backup can be compared with the source, including a byte-for-byte comparison of all the files.

All backup tasks can be specified with a script, or by using the GUI. The backup process can also be paused and resumed.

[100% FREE award granted by Softpedia](http://www.softpedia.com/progClean/SS-Backup-Clean-245148.html)

## 2. Installation

[Download the main executable](https://sourceforge.net/projects/ss-backup/files/latest/download) and run it.

### 2.1 Command-line Options
When the executable is followed with a script file name, it will load the script automatically.  File names with spaces must be quoted (double quotes ").

SS-Backup starts paused.  If you'd like it to run the script automatically, use a "-run" command-line option.

## 3. Functionality

The paradigm of SS-Backup is to have a queue of tasks, which are executed in first-in-first-out order.  The task engine runs in it's own thread, which can be paused and resumed at the user's leisure (by choosing "Pause/Resume" on the "Tasks" menu, pressing "Ctrl+P" on the keyboard or by clicking the pause/play button next to the tasks combo-box).

**Note that exiting (quitting) SS-Backup is implemented as a task, so the engine thread must be running for the program to exit.**

To add a task to the queue, fill in the fields and choose "Add" from the "Tasks" menu, or press "Enter" on the keyboard.  To delete a task from the queue, select it on the list and choose "Remove" from the "Tasks" menu, or press "Shift-Delete" on the keyboard.

### 3.1 Folder Tree

Even though the folder tree provided might suggest that only local files and folders can be used, this is not the case.  You could type a network path into the fields before adding the task.  Such a folder might look like "\\\\server\\share\\backup\\", for instance.

To refresh the tree, close and reopen the branch you want refreshed.

### 3.2 Backup

The main function of SS-Backup is to perform a backup.  It does a straight copy from the source file or folder to the destination folder.  The file is copied if: 

- The file does not exist on the destination
- The file exists on the destination, but the source is newer
- The source and destination files have the same modified time-stamp, but the size differs
- The modified time-stamps and sizes are the same, but the contents differ (optional)

It is recommended to have the source and destination folders on different drives, so that when the one fails, the other has all your data ready to use.

All folders are traversed recursively.

### 3.3 Clone

Similar to Backup, but it performs the copy if anything differs (file size, modification date or, optionally, contents).

### 3.4 Synchronise

Synchronising does the same as backup, but in both directions.  The source, in this case, must also be a folder.  If you want to synchronise single files within a folder you have to call Backup twice: once for each direction.

### 3.5 Compare

The compare task performs a compare on the source and destination folders, storing the result in a log file.  Files are compared for modification time-stamp, size and, optionally, contents.  If the file exists only in one or the other, this fact is also logged.

### 3.6 Clean

Cleaning is useful for backups of active projects, where the source changes structure often.  The source and destination folders are compared, and destination files and folders that does not exist in the source folder are deleted.

### 3.7 Exit

Exiting SS-Backup is also implemented as a task, so the engine thread must be running for the program to exit.

This task is added by clicking the window close button, choosing "Exit" on the "File" menu, or pressing "Alt+F4" on the keyboard.

## 4. Options

All the main tasks (Backup, Synchronise, Compare and Clean) come with options, which are discussed in this section.

### 4.1 Incremental

For backups, the destination file is moved to a time-stamped folder before being replaced.  For cleaning, the file is moved to the time-stamped folder instead of being deleted.  This option must be a folder (end in a '\\').

It is strongly recommended that the destination and incremental folders are on the same drive, so that moving involves a "rename" operation, rather than a "copy-delete" cycle.

### 4.2 Contents

By enabling the Contents option, Backup, Synchronise and Compare also compares the contents of the source and destination files.  Backup and Synchronise will perform the copy when the contents differ, whereas Compare will log that there is a difference.

### 4.3 Log

All operations are logged to the file provided.  This is optional, and all tasks will complete successfully without a log file specified.

SS-Backup does not report errors to the user, so a log-file is useful to confirm that a new backup script works correctly.

## 5. Scripts

To create a script, pause the engine, add some tasks to the queue and choose "Save Script" from the "File" menu.  To load a script, choose "Load Script" from the "File" menu.

For those of us who prefer writing scripts directly, however, here follows the file format:

A script file is divided into task cards, which in turn are divided into lines.  Comments (lines that start with '%') are ignored, as are empty lines and trailing and leading spaces.  Lines are parsed literally, so do not quote, and use UTF-8 encoding.

All task cards start with a header line, with the task (or option) between square brackets.  Valid headers 
are:

- \[Log\]
    - Followed by a single line specifying the log file for subsequent tasks, or "Off", which disables logging.
- \[Contents\]
    - Followed by a single line specifying "On" or "Off".
- \[Incremental\]
    - Followed by a single line specifying the incremental folder for subsequent tasks, or "Off", which disables the incremental feature.
- \[Backup\]
    - Followed by two lines, the first specifying the source file or folder and the second the destination folder.
- \[Clone\]
    - Followed by two lines, the first specifying the source file or folder and the second the destination folder.
- \[Synchronise\]
    - Followed by two lines, the first specifying the source folder and the second the destination folder.
- \[Compare\]
    - Followed by two lines, the first specifying the source folder and the second the destination folder.
- \[Clean\]
    - Followed by two lines, the first specifying the source folder and the second the destination folder.
- \[Script\]
    - Followed by a script file name.  If no extension is specified, ".BSc" is appended.  If no path is specified, the same path as the current script file is used.
- \[Exit\]
    - If the current script is the root script, adds an Exit task to the queue.  Alternatively, if the current script is a child script, discards the rest of the script file and returns to parsing the parent script.

When a script is called, the loaded script inherits the current script's "Contents" state, but uses the default for the other options, which are "no logging" and "no incremental".  This is useful for creating a script for every-day backups, and then another, which calls the every-day script, but also specifies contents checking, to be run over weekends.  Then only one script needs to be maintained.

Script recursion is limited to 1000 levels, so accidentally adding a circular reference should not make SS-Backup crash.

## 6. Bugs

Please post any bugs you may find on the [discussions page](https://sourceforge.net/p/ss-backup/discussion/bugs).

## 7. Future Version Ideas

Ideas for a future version include:

- Exclude a list of file extensions from the backup
- Display errors as a message-box upon exit
- A shut-down task, to shut down the computer when finished
- Complete copy (copy everything, always)

If you have any other ideas, please do not hesitate to [post them](https://sourceforge.net/p/ss-backup/discussion/create_topic) on the discussions page.

## 8. Updates

I often upload the same version more than once, with subsequent uploads incorporating some minor bug-fixes.  The file time-stamp can be used as an indication of version, but the build time-stamp, available in the "About" box, is more accurate.

## 9. Source

The source is available from the [git repository](https://sourceforge.net/p/ss-backup/code/) and [GitHub](https://github.com/jpt13653903/SS-Backup).  It is a MinGW project, with Code::Blocks as IDE.

Please [contact me](https://sourceforge.net/p/ss-backup/discussion/create_topic) if you are enthusiastic enough to have ported the project to Mac OS X, Linux or your favourite operating system.  I'd like to post the ported versions.

[[members limit=20]]
[[download_button]]

