# DISCONTINUED

# dark
Only will be light after chaos.

## TODO:
## Bot:
	- [] Try to add templates to avoid declaring the function's types;

	### Bot/Bot.*:
		- [x] Remake message entries;
		- [x] Create a message entires that accepts json, to parse and instanciate in the heap;
		- [x] Put std::queue<Postmail::Message> _messages into heap using std::_unique_ptr<>;
		- [x] Set message directly into Session in _doConsumeQueue();
		- [x] Change _doProcessMessage to take only a Session instance;
	
	### Bot/Session.*:
		- [x] Put Postmail::Message _message into heap using std::unique_ptr<>;
		- [x] Put Dialog _dialog into heap using std::unique_ptr<>;

## Server:
	### Server/Server.*:
		- [] Put std::vector<Route> _routes into heap using std::unique_ptr<>;

	### Server/Request.*:
		- [] Put Struct::Attributes _attributes into heap using std::unique_ptr<>;
