function getCookie(name: string): string | null {
	let matches = document.cookie.match(new RegExp(
		"(?:^|; )" + name.replace(/([\.$?*|{}\(\)\[\]\\\/\+^])/g, '\\$1') + "=([^;]*)"
	));

	return matches ? decodeURIComponent(matches[1]) : null;
}

function setCookie(name, value, options = {}): void {

	options = {
		path: '/',
		...options
	};

	if (options.expires && options.expires instanceof Date) {
		options.expires = options.expires.toUTCString();
	}

	let updatedCookie = encodeURIComponent(name) + "=" + encodeURIComponent(value);

	for (let optionKey in options) {
		updatedCookie += "; " + optionKey;
		let optionValue = options[optionKey];
		if (optionValue !== true) {
			updatedCookie += "=" + optionValue;
		}
	}

	document.cookie = updatedCookie;
}

function deleteCookie(name: string): void {
	setCookie(name, '', {'max-age': -1});
}

function getContent(route: string = '') {
	let url = new URL(window.location.href);

	let href = url.origin;
	let pathname = route ? url.pathname.replace(route, `${route}/xhr`) : `/xhr${url.pathname}`;
	let params = url.search;

	Base.Common.Query.Send(`${href}${pathname}${params}`, null, {request: ''});
}