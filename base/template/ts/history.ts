namespace Base {
	export namespace Common {

		export class History {

			public static Initialization() {
				$(window).on('popstate', event  => {
					let state = (event.originalEvent as PopStateEvent).state;
					if (!state) return;

					Base.Common.Query.SendData(state.xhr, {no_history: 1}, state.handler ? eval(state.handler) : null, {request: ''});
				});
			}

			public static Replace(address, xhr) {
				window.history.replaceState({xhr: xhr}, '', address);
			}

		}

	}
}