namespace Base {
	export namespace Common {

		export class GlobalParams {
			private static param = {};

			public static Set(name :string, value :any) {
				GlobalParams.param[name] = value;
			}

			public static Get(name) :any {
				return GlobalParams.param[name];
			}

		}

		type TypeRequestParams = {
			method			?: 'get' | 'post',
			request			?: string,
			processData		?: boolean,
			contentType		?: string | false
		}

		type TypeResponse = {
			state			: 'ok' | 'message',
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
				}
			}

		}

		export class Section {
			private $_elem			: JQuery

			public constructor($_elem: JQuery) {
				this.$_elem = $_elem;
			}

			public Fill(...contents) {
				this.$_elem.empty();
				for (let i in contents) {
					if (Array.isArray(contents[i])) for (let j in contents[i]) this.$_elem.append(contents[i][j]);
					else this.$_elem.append(contents[i]);
				}
			}

			public Push(...contents) {
				for (let i in arguments) {
					if (Array.isArray(arguments[i])) for (let j in arguments[i]) this.$_elem.append(arguments[i][j]);
					else this.$_elem.append(arguments[i])
				}
			}

		}

		export class Layout {

			public static Initialization() {  }

		}

	}
}