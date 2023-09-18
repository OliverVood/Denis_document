namespace Base {
	export namespace Common {

		type TypeRequestParams = {
			method					?: 'get' | 'post',
			request					?: string,
			processData				?: boolean,
			contentType				?: string | false
		}

		type ResponseBase<Type, Data> = {
			type					: Type,
			data					: Data
		}

		type ResponseHistoryData	= { address: string, xhr: string, handler: string };
		type ResponseSectionData	= { section: string, html: string, empty: boolean };
		type ResponseNoticeData		= { type: 'ok' | 'info' | 'error', notice: string };

		type ResponseHistory		= ResponseBase<'history', ResponseHistoryData>
		type ResponseSection		= ResponseBase<'section', ResponseSectionData>
		type ResponseNotice			= ResponseBase<'notice', ResponseNoticeData>
		type ResponseDebugger		= ResponseBase<'debugger', any>

		type Response 				= ResponseHistory | ResponseSection | ResponseDebugger;

		export class Query {

			public static SendData(address :string, data :Object, handler ?:Function, params ?:TypeRequestParams) {
				let method			: string			= 'post';
				let request 		: string			= GlobalParams.Get('xhr');
				let contentType		: string | false	= 'application/x-www-form-urlencoded;charset=UTF-8';
				let processData		: boolean			= true;

				if (params) {
					if (params.method) method = params.method;
					if (params.request !== undefined) request = params.request;
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

			private static Response(response: Response, handler?: Function) {
				for (const i in response) Query.Execute(response[i].type, response[i].data, handler);
			}

			private static Execute(type: string, data: any, handler?: Function): void {
				switch (type) {
					case 'history': Query.ExecuteHistory(data); break;
					case 'section': Query.ExecuteSection(data); break;
					case 'notice': Query.ExecuteNotice(data); break;
					case 'data': Query.ExecuteHandler(handler, data); break;
					case 'debugger': Debugger.Append(data); break;
				}
			}

			private static ExecuteHistory(data: ResponseHistoryData): void {
				window.history.pushState({xhr: data.xhr, handler: data.handler}, '', data.address);
			}

			private static ExecuteSection(data: ResponseSectionData): void {
				let $section = $(data.section)
				if (data.empty) $section.empty();
				$section.append(data.html);/*Admin.Common.Layout.main.Fill*/
			}

			private static ExecuteNotice(data: ResponseNoticeData): void {
				Base.Common.Notice.Create(data.type, data.notice);
			}

			private static ExecuteHandler(handler: Function | null, data: any): void {
				if (handler) handler(data);
			}

		}

	}
}