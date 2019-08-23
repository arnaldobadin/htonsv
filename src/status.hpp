#ifndef STATUS_H
#define STATUS_H

#include <string>

namespace Status {

	struct Code {
		int id;
		std::string name;
	};

	static const Code Continue = {100, "Continue"};
	static const Code SwitchingProtocols = {101, "SwitchingProtocols"};
	static const Code Processing = {102, "Processing"};
	static const Code EarlyHints = {103, "EarlyHints"};
	static const Code OK = {200, "OK"};
	static const Code Created = {201, "Created"};
	static const Code Accepted = {202, "Accepted"};
	static const Code NonAuthoritativeInformation = {203, "NonAuthoritativeInformation"};
	static const Code NoContent = {204, "NoContent"};
	static const Code ResetContent = {205, "ResetContent"};
	static const Code PartialContent = {206, "PartialContent"};
	static const Code MultiStatus = {207, "MultiStatus"};
	static const Code AlreadyReported = {208, "AlreadyReported"};
	static const Code IMUsed = {226, "IMUsed"};
	static const Code MultipleChoices = {300, "MultipleChoices"};
	static const Code MovedPermanently = {301, "MovedPermanently"};
	static const Code Found = {302, "Found"};
	static const Code SeeOther = {303, "SeeOther"};
	static const Code NotModified = {304, "NotModified"};
	static const Code UseProxy = {305, "UseProxy"};
	static const Code TemporaryRedirect = {307, "TemporaryRedirect"};
	static const Code PermanentRedirect = {308, "PermanentRedirect"};
	static const Code BadRequest = {400, "BadRequest"};
	static const Code Unauthorized = {401, "Unauthorized"};
	static const Code PaymentRequired = {402, "PaymentRequired"};
	static const Code Forbidden = {403, "Forbidden"};
	static const Code NotFound = {404, "NotFound"};
	static const Code MethodNotAllowed = {405, "MethodNotAllowed"};
	static const Code NotAcceptable = {406, "NotAcceptable"};
	static const Code ProxyAuthenticationRequired = {407, "ProxyAuthenticationRequired"};
	static const Code RequestTimeout = {408, "RequestTimeout"};
	static const Code Conflict = {409, "Conflict"};
	static const Code Gone = {410, "Gone"};
	static const Code LengthRequired = {411, "LengthRequired"};
	static const Code PreconditionFailed = {412, "PreconditionFailed"};
	static const Code PayloadTooLarge = {413, "PayloadTooLarge"};
	static const Code URITooLong = {414, "URITooLong"};
	static const Code UnsupportedMediaType = {415, "UnsupportedMediaType"};
	static const Code RangeNotSatisfiable = {416, "RangeNotSatisfiable"};
	static const Code ExpectationFailed = {417, "ExpectationFailed"};
	static const Code ImATeapot = {418, "ImATeapot"};
	static const Code UnprocessableEntity = {422, "UnprocessableEntity"};
	static const Code Locked = {423, "Locked"};
	static const Code FailedDependency = {424, "FailedDependency"};
	static const Code UpgradeRequired = {426, "UpgradeRequired"};
	static const Code PreconditionRequired = {428, "PreconditionRequired"};
	static const Code TooManyRequests = {429, "TooManyRequests"};
	static const Code RequestHeaderFieldsTooLarge = {431, "RequestHeaderFieldsTooLarge"};
	static const Code UnavailableForLegalReasons = {451, "UnavailableForLegalReasons"};
	static const Code InternalServerError = {500, "InternalServerError"};
	static const Code NotImplemented = {501, "NotImplemented"};
	static const Code BadGateway = {502, "BadGateway"};
	static const Code ServiceUnavailable = {503, "ServiceUnavailable"};
	static const Code GatewayTimeout = {504, "GatewayTimeout"};
	static const Code HTTPVersionNotSupported = {505, "HTTPVersionNotSupported"};
	static const Code VariantAlsoNegotiates = {506, "VariantAlsoNegotiates"};
	static const Code InsufficientStorage = {507, "InsufficientStorage"};
	static const Code LoopDetected = {508, "LoopDetected"};
	static const Code NotExtended = {510, "NotExtended"};
	static const Code NetworkAuthenticationRequired = {511, "NetworkAuthenticationRequired"};

};

#endif