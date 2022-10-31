type TypeRequestParams = {
	method			?: 'get'|'post',
	request			?: string,
	processData		?: boolean,
	contentType		?: string
}
type TypeResponse = {
	state			: 'ok' | 'message',
	data			: any
}

class GlobalParams {
	static param = {};

	static Set(name :string, value :any) {
		GlobalParams.param[name] = value;
	}

	static Get(name) :any {
		return GlobalParams.param[name];
	}

}

namespace Base {
	export namespace Common {

		export function RequestData(address :string, data :Object, handler ?:Function, params ?:TypeRequestParams) {
			let method			= 'post';
			let request 		= GlobalParams.Get('request');
			let processData		= false;
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
				success			: function(response) { RequestResponse(response, (handler) ? handler : null); },
				error			: function(response) { console.log('request failed: ' + address); console.log(response); }
			});
		}

		export function Request(address :string, handler ?:Function, params ?:TypeRequestParams) {
			RequestData(address, {}, handler, params);
		}

		export function RequestForm(form: JQuery, handler ?:Function, params ?:TypeRequestParams) {
			let _form = form[0] as HTMLFormElement;

			RequestData(form.attr('action'), new FormData(_form), handler, params);
		}

		function RequestResponse(response :TypeResponse, handler :Function) {
			switch (response['state']) {
				case 'ok': if (handler) handler(response['data']); break;
			}
		}

	}
}