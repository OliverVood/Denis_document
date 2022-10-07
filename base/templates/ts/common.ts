type TypeRequestParams = {
	method			?: 'get'|'post',
	request			?: string,
	processData		?: boolean,
	contentType		?: string
}

namespace Base {

	export namespace Common {

		export function RequestData(address: string, data: Object, params?: TypeRequestParams) {
			let method			= 'post';
			let request 		= 'http://documents/';
			let processData		= true;
			let contentType		= 'application/x-www-form-urlencoded;charset=UTF-8';

			if (params) {
				if (params.method) method = params.method;
				if (params.request) request = params.request;
				if (params.processData !== undefined) processData = params.processData;
				if (params.contentType !== undefined) contentType = params.contentType;
			}

			$.ajax({
				url				: `${request}${address}`,
				method			: method,
				dataType		: 'json',
				data 			: data,
				processData		: processData,
				contentType		: contentType,
				cache			: false,
				// beforeSend: function() { if (funcBeforeSend) funcBeforeSend(); },
				// complete: function() { if (funcComplete) funcComplete(); },
				success: function(response) { RequestResponse(response/*, {function: funcSuccess}*/); },
				error			: function(response) { console.log('request failed: ' + address); console.log(response); }
			});
		} // END FUNCTION RequestData

		function RequestResponse(response) {
			console.log(response);
		} // END FUNCTION RequestResponse

	} // END NAMESPACE COMMON

} // END NAMESPACE SITE