namespace Site {
	export namespace General {

		export function On() {
			Base.Common.Query.Send('/donations', data => { Site.Common.Window.Create(data.html, 'Поддержать проект'); }); //TODO Actions;
		}

	}
}