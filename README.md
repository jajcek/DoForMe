Development release 9.08.2012
===================================================
TODO:
- Sorting actions by time in actionsAll. Then the index equals to number of item on the actions list.

Development release 8.08.2012
===================================================
- Time format set to H:MM:SS.
- Setting actions list after adding action.
- Removed 'Commands time interval' option from action settings (it will be some kid of global option).
- 'Every day' option in action settings implemented (signals created in QT Designer).
- Lighter color for cell with action on calendar.
- Smaller font size for "X action(s)" text.
- Inform a user that he is trying to add action to the past.
- Information dialog that the script wasn't selected.

Development release 6.08.2012
===================================================
- ActionSettingsDialog renamed to ActionSettings.
- DetailedCalendar renamed to ActionCalendar.
- DAYS structure removed, the values moved to ActionSettings.
- Methods for managin actions in Action and ActionCalendar class.
- Setting repetitions of actions on the calendar.

Development release 3.08.2012
===================================================
- Adding 'get's methods for ActionSettingsDialog.
- New DAYS structure which keeps values for days of week (all that kind of values will be kept in constants.h file.
- Conf structure renamed to CONF.

Development release 3.08.2012
===================================================
- Shortcuts for new script, save option.
- Settings dialog for actions while adding action.
- Doxygen comments for Conf.f, Script.h, ScriptsManager.h, key.h as well as some comments for lua_engine.h.
- Fix for the warning about flow control path (not returning a value for every control path in method).

Development release 2.08.2012
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
