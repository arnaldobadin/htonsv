#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <string>
#include <vector>

namespace Protocol {

	struct Item {
		unsigned int id = 0;
		std::string name = "None";
	};

	enum class Method : unsigned {
		GET = 1, POST = 2
	};

	enum class Code : unsigned {
		CONTINUE = 100, SWITCHING_PROTOCOLS = 101, PROCESSING = 102, EARLY_HINTS = 103,

		OK = 200, CREATED = 201, ACCEPTED = 202, NON_AUTHORITATIVE_INFORMATION = 203,
		NO_CONTENT = 204, RESET_CONTENT = 205, PARTIAL_CONTENT = 206, MULTI_STATUS = 207,
		ALREADY_REPORTED = 208, IM_USED = 226,

		MULTIPLE_CHOICES = 300, MOVED_PERMANENTLY = 301, FOUND = 302, SEE_OTHER = 303,
		NOT_MODIFIED = 304, USE_PROXY = 305, TEMPORARY_REDIRECT = 307, PERMANENT_REDIRECT = 308,

		BAD_REQUEST = 400, UNAUTHORIZED = 401, PAYMENT_REQUIRED = 402, FORBIDDEN = 403,
		NOT_FOUND = 404, METHOD_NOT_ALLOWED = 405, NOT_ACCEPTABLE = 406,
		PROXY_AUTHENTICATION_REQUIRED = 407, REQUEST_TIMEOUT = 408, CONFLICT = 409,
		GONE = 410, LENGTH_REQUIRED = 411, PRECONDITION_FAILED = 412, PAYLOAD_TOO_LARGE = 413,
		URI_TOO_LONG = 414, UNSUPPORTED_MEDIA_TYPE = 415, RANGE_NOT_SATISFIABLE = 416,
		EXPECTATION_FAILED = 417, IM_A_TEAPOT = 418, UNPROCESSABLE_ENTITY = 422, LOCKED = 423,
		FAILED_DEPENDENCY = 424, UPGRADE_REQUIRED = 426, PRECONDITION_REQUIRED = 428,
		TOO_MANY_REQUESTS = 429, REQUEST_HEADER_FIELDS_TOO_LARGE = 431, UNAVAILABLE_FOR_LEGAL_REASONS = 451,
		
		INTERNAL_SERVER_ERROR = 500, NOT_IMPLEMENTED = 501, BAD_GATEWAY = 502,
		SERVICE_UNAVAILABLE = 503, GATEWAY_TIMEOUT = 504, HTTP_VERSION_NOT_SUPPORTED = 505,
		VARIANT_ALSO_NEGOTIATES = 506, INSUFFICIENT_STORAGE = 507, LOOP_DETECTED = 508,
		NOT_EXTENDED = 510, NETWORK_AUTHENTICATION_REQUIRED = 511
	};

	namespace {
		static const std::vector<Item> _method_map = {
			{1, "GET"}, {2, "POST"}
		};

		static const std::vector<Item> _code_map = {
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

		inline Protocol::Item find(const std::vector<Item>& items, unsigned int id) {
			for (size_t i = 0; i < items.size(); i++) {
				if (id == items[i].id) return items[i];
			}
			Item item;
			return item;
		}

		inline Protocol::Item find(const std::vector<Item>& items, const std::string& name) {
			for (size_t i = 0; i < items.size(); i++) {
				if (name == items[i].name) return items[i];
			}
			Item item;
			return item;
		}
	}

	inline Protocol::Item Methods(unsigned int id) {return find(_method_map, id);}
	inline Protocol::Item Methods(Protocol::Method method) {return find(_method_map, static_cast<unsigned int>(method));}
	inline Protocol::Item Methods(const std::string& name) {return find(_method_map, name);}

	inline Protocol::Item Codes(unsigned int id) {return find(_code_map, id);}
	inline Protocol::Item Codes(Protocol::Code code) {return find(_code_map, static_cast<unsigned int>(code));}
	inline Protocol::Item Codes(const std::string& name) {return find(_code_map, name);}
};

#endif