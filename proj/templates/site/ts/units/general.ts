namespace Site {
	export namespace General {

		export function OnDonations(data) {
			Site.Common.Window.Create(data.html, 'Поддержать проект');
		}

	}
}