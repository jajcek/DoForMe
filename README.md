Development release 29.08.2012
===================================================
Fixes
---------------------------------------------------
- Cancel option in closing dialog was closing the app.
- Parsing script code didn't include parsing special keys in sendText api function.

Development release 28.08.2012
===================================================
Functionalities
---------------------------------------------------
- Validating script while adding to calendar.
- Parse script button.
- Ask user whether he wants to save unsaved script before closing app.
- Double click on tray icon restores main window.

Fixes
---------------------------------------------------
- Save action in menu wasn't disabled when user saved a script.
- You couldn't close the window by pressing X, when the script wasn't selected.

Development release 27.08.2012
===================================================
Functionalities
---------------------------------------------------
- Tray icon which contains all actions that are left for the current day.

Fixes
---------------------------------------------------
- Tray icon wasn't removed during app close.
- The actions weren't queued if they were close to each other.
- If the actions have been set at the same time, the action with lower Id will be performed first.

Development release 19.08.2012
===================================================
Functionalities
---------------------------------------------------
- Moving actions on the calendar.
TODO - tabs for scripts, saving when changed modified script
ask how to not emit textChanged when text is changed programatically, but only manually

Development release 18.08.2012
===================================================
Functionalities
---------------------------------------------------
- Buttons for calendar and script removing are disabled. They enable when the appropriate action has been made by a user.

Development release 17.08.2012
===================================================
Functionalities
---------------------------------------------------
- importing scripts.
- removing scripts from the scripts list.
- combobox for choosing scripts instead of selecting them on the scripts list first.

Development release 16.08.2012
===================================================
- Saving and loading actions by using SQLite database.
- 'Save on close' functionality.
- Fixed issue that allowed user to detach non-repeated action to infinity which caused bugs.
- Fixed sorting actions table (it was sorting 1, 10, 2, 3... and the purpose was 1, 2, ..., 10)
- Fixed issue which led to not loading excluded dates from repetitions.
- Fix: crash when removing action with no action selected.
- Fix: an invalid excluding date was put when there were no excluded dates at all.

Development release 15.08.2012
===================================================
- Saving actions into database.
- Fixed issue that cause not to turn off highlights when two actions were added in the same date in a row.

Development release 14.08.2012
===================================================
- Edit action functionality.
- 'Old time' info dialog on button in 'add action settings' dialog.
- Fix issue that caused not to highlight newly added actions.

Development release 13.08.2012
===================================================
- Fixed issue that caused undetermined order of actions list.
- Exclamation mark as conflict (the yeelow background is still).
- Run script from text field instead of code from script object.
- Detach action functionality.
- Fixes for highlighting after detaching and addin action.
- Remove action(s) functionality.

Development release 11.08.2012
===================================================
- Highlighting repeated action on calendar if selected one of them.
- Message box that inform about old time moved to ActionSettings class.
- Inability to add two actions for the same time (doesn't affect repetition).
- Showing conflicts (actions at the same time, it is possible to achieve that by using repetition).
- Changed list widget to table wisget for actions list.
- Selecting actions from the "table" list.

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
