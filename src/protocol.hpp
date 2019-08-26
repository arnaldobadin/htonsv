#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <map>

namespace Protocol {

	struct Item {
		unsigned int id;
		std::string name;

		Item() {
			this->id = 0;
			this->name = "None";
		}

		Item(unsigned int id, std::string name) {
			this->id = id;
			this->name = name;
		}
	};

	namespace {
		static const std::map<const unsigned int, const std::string> _methods = {
			{0, "None"}, {1, "GET"}, {2, "POST"}
		};

		static const std::map<const unsigned int, const std::string> _status = {
			{0, "None"},
			
			{100, "Continue"}, {101, "SwitchingProtocols"}, {102, "Processing"}, {103, "EarlyHints"},
			
			{200, "OK"}, {201, "Created"}, {202, "Accepted"}, {203, "NonAuthoritativeInformation"},
			{204, "NoContent"}, {205, "ResetContent"}, {206, "PartialContent"}, {207, "MultiStatus"},
			{208, "AlreadyReported"}, {226, "IMUsed"},
			
			{300, "MultipleChoices"}, {301, "MovedPermanently"}, {302, "Found"}, {303, "SeeOther"},
			{304, "NotModified"}, {305, "UseProxy"}, {307, "TemporaryRedirect"}, {308, "PermanentRedirect"},

			{400, "BadRequest"}, {401, "Unauthorized"}, {402, "PaymentRequired"}, {403, "Forbidden"},
			{404, "NotFound"}, {405, "MethodNotAllowed"}, {406, "NotAcceptable"},
			{407, "ProxyAuthenticationRequired"}, {408, "RequestTimeout"}, {409, "Conflict"},
			{410, "Gone"}, {411, "LengthRequired"}, {412, "PreconditionFailed"}, {413, "PayloadTooLarge"},
			{414, "URITooLong"}, {415, "UnsupportedMediaType"}, {416, "RangeNotSatisfiable"},
			{417, "ExpectationFailed"}, {418, "ImATeapot"}, {422, "UnprocessableEntity"}, {423, "Locked"},
			{424, "FailedDependency"}, {426, "UpgradeRequired"}, {428, "PreconditionRequired"},
			{429, "TooManyRequests"}, {431, "RequestHeaderFieldsTooLarge"}, {451, "UnavailableForLegalReasons"},
			
			{500, "InternalServerError"}, {501, "NotImplemented"}, {502, "BadGateway"},
			{503, "ServiceUnavailable"}, {504, "GatewayTimeout"}, {505, "HTTPVersionNotSupported"},
			{506, "VariantAlsoNegotiates"}, {507, "InsufficientStorage"}, {508, "LoopDetected"},
			{510, "NotExtended"}, {511, "NetworkAuthenticationRequired"}
		};
	}

	class Table {
		public:
			Table(const std::map<const unsigned int, const std::string>& map) {
				_map = map;
			}

			struct Item {
				unsigned int id;
				std::string name;

				Item() {
					this->id = 0;
					this->name = "None";
				}

				Item(unsigned int id, std::string name) {
					this->id = id;
					this->name = name;
				}
			};

			Table::Item operator()(unsigned int id) {
				Table::Item item;

				typename std::map<const unsigned int, const std::string>::iterator iterator = _map.find(id);
				if (iterator == _map.end()) return item;

				item.id = id;
				item.name = iterator->second;
				return item;
			}

			Table::Item operator()(const std::string& name) {
				Table::Item item;

				typename std::map<const unsigned int, const std::string>::iterator iterator;
				for (iterator = _map.begin(); iterator != _map.end(); ++iterator) {
					if (iterator->second == name) {
						item.id = iterator->first;
						item.name = name;
						return item;
					}
				}
				return item;
			}

		private:
			std::map<const unsigned int, const std::string> _map;
	};

	static Table Method(_methods);
	static Table Status(_status);
};

#endif