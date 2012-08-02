Development release 1.08.2012
===================================================
- No extension of the file on the scripts list.
- Modified state for script file.
- Configuration structure "conf.h" which keeps all important values (script folder, extension for file etc.).
- Saving scripts.

Development release 1.08.2012
===================================================
- Changed way for adding new scripts.
- Now the user types file name (the script has no description and title, just file name).
- On the scripts list there's file name instead of title.
- Selection of the script on the list has been implemented.

Development release 31.07.2012
===================================================
- Script manager class for managing all scripts.
- Title is displayed on the scripts list instead of file name.
- Validating scripts title (for duplicates) on app start. Input dialog for renaming if there is a conflict.
- Validating scripts title/file name during script adding.
- Clean ups for scripts.
- Fix issue that caused scripts loader to loop infinitely.

Development release 30.07.2012
===================================================
- Fix for New File window, if the scripts directory didn't exists you couldn't create a file
- Loading all scripts when app is run

Development release 29.07.2012
===================================================
- Completely different GUI with tool bar
- New script window

Development release 28.07.2012
===================================================
- Button that allows to add actions on a specified day
- Add action button placed instead of Save and Save as buttons (we can save it from the menu above). The add action button can also invoke saving action, because the script has to be saved before added to actions list.
- Save and Save as now save the file, because actually it wasn't...
- Adding item to a specified day
- List <-> Calendar interaction (displaying actions for the specified day)

Development release 18.07.2012
===================================================
- LuaApiEngine doxygen comments
- Modified LuaApiEngine::getSpecialKey() function (now it returns number of read symbols)
