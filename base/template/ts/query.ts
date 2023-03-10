namespace Base {
	export namespace Common {

		type TypeRequestParams = {
			method			?: 'get' | 'post',
			request			?: string,
			processData		?: boolean,
			contentType		?: string | false
		}

		type TypeResponse = {
			state			: 'ok' | 'notice',
			data			: any
		}

		export class Query {

			public static SendData(address :string, data :Object, handler ?:Function, params ?:TypeRequestParams) {
				let method			: string			= 'post';
				let request 		: string			= GlobalParams.Get('request');
				let contentType		: string | false	= 'application/x-www-form-urlencoded;charset=UTF-8';
				let processData		: boolean			= true;

				if (params) {
					if (params.method) method = params.method;
					if (params.request) request = params.request;
					if (params.contentType !== undefined) contentType = params.contentType;
					if (params.processData !== undefined) processData = params.processData;
				}

				$.ajax({
					url				: `${request}${address}`,
					method			: method,
					dataType		: 'json',
					data 			: data,
					contentType		: contentType,
					processData		: processData,
					cache			: false,
					// beforeSend: function() { if (funcBeforeSend) funcBeforeSend(); },
					// complete: function() { if (funcComplete) funcComplete(); },
					success			: function(response) { Query.Response(response, (handler) ? handler : null); },
					error			: function(response) { console.log('request failed: ' + address); console.log(response); }
				});
			}

			public static Send(address :string, handler ?:Function, params ?:TypeRequestParams) {
				Query.SendData(address, {}, handler, params);
			}

			public static SendForm(form: JQuery, handler ?:Function) {
				let _form = form[0] as HTMLFormElement;

				Query.SendData(form.attr('action'), new FormData(_form), handler, {contentType: false, processData: false});
			}

			public static SubmitForm(th, handler ?:Function) {
				Query.SendForm($(th).closest('form'), handler);
			}

			public static SubmitFormEvent(e, handler ?:Function) {
				Query.SendForm($(e.currentTarget).closest('form'), handler);
			}

			private static Response(response :TypeResponse, handler :Function) {
				switch (response['state']) {
					case 'ok': if (handler) handler(response['data']); break;
					case 'notice': Base.Common.Notice.Create(response['type'], response['notice']); break;
				}
			}

		}

	}
}