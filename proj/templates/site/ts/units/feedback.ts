namespace Site {
	export namespace Feedback {
		let wind = null;

		export function On() {
			Base.Common.Query.Send('/feedback', data => { wind = Site.Common.Window.Create(data.html, 'Обратная связь'); }); //TODO Actions;
		}

		export function Do() {
			wind.Close();
			Base.Common.Notice.Ok('Ваша заявка принята')
		}

	}
}