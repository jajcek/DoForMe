================================================
Release 18.07.2012
================================================
- Mouse simulation engine
	- prepareLeftDown();
	- prepareRightDown();
	- prepareMiddleDown();
	- prepareLeftDownAt( x, y );
	- prepareRightDownAt( x, y );
	- prepareMiddleDownAt( x, y );

	- prepareLeftUp();
	- prepareRightUp();
	- prepareMiddleUp();
	- prepareLeftUpAt( x, y );
	- prepareRightUpAt( x, y );
	- prepareMiddleUpAt( x, y );

	- prepareLeftClick();
	- prepareRightClick();
	- prepareMiddleClick();
	- prepareLeftClickAt( x, y );
	- prepareRightClickAt( x, y );
	- prepareMiddleClickAt( x, y );

	- prepareLeftDoubleClick();
	- prepareLeftDoubleClickAt( x, y );

	- prepareMoveTo();
	
- Keyboard simulation engine
	- sendText( text )
	- ability to use special keys in {} brackets e.g. sendText( "{tab}a{n}b" ) will start with a tabulator and break the line between 'a' and 'b'

- Other commands
	- sleep( time_in_milliseconds )
	
- 'About' dialog
- Custom calendar

================================================