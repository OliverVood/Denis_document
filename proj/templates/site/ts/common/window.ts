namespace Site {
	export namespace Common {

		export class Window {
			/* Variables */
			private static iter = 0;
			private static windows = {};

			/* Elements */
			public static $windows = null;

			static Create(html: string, title: string | null = null): Instance {
				return Window.New(html, title);
			}

			static Interactive(html: string | JQuery, title: string | null, btns: any = [], funcYes: Function | null = null, funcNo: Function | null = null, funcCancel: Function | null = null): Instance {
				let $container = $('<div/>', {class: 'view general interactive'});
				let $content = $('<div/>', {class: 'contain'});
				let $btns = $('<div/>', {class: 'btns'});

				$container.append(
					$content.append(
						html
					),
					$btns
				);

				let _wind = Window.New($container, title);

				for (let i in btns) {
					let $input = $('<input/>', {type: 'button', value: btns[i][1]});

					$btns.append(
						$input
					);

					switch (btns[i][0]) {
						case 'yes': $input.on('click', () => OnYes((btns[i][2] !== false))); break;
						case 'no': $input.on('click', () => OnNo((btns[i][2] !== false))); break;
						case 'cancel': $input.on('click', () => OnCancel((btns[i][2] !== false))); break;
					}
				}

				function OnYes(autoClose: boolean = true): void {
					if (funcYes) funcYes();
					if (autoClose) _wind.Close();
				}

				function OnNo(autoClose: boolean = true): void {
					if (funcNo) funcNo();
					if (autoClose) _wind.Close();
				}

				function OnCancel(autoClose: boolean = true): void {
					if (funcCancel) funcCancel();
					if (autoClose) _wind.Close();
				}


				return _wind;
			}

			private static New(html: string | JQuery, title: string | null): Instance {
				if (!Window.$windows) {
					Window.$windows = $('<div/>', {class: 'view general windows'});
					$('body').append(Window.$windows);
				}

				Window.iter++;
				let _wind = new Instance(Window.iter, html, title);
				Window.windows[Window.iter] = _wind;

				return _wind;
			}

			static Delete(id: number): void {
				delete Window.windows[id];
			}

		}

		class Instance {
			/* Variables */
			id				: number;

			/* Elements */
			$instance		: JQuery;

			constructor(id: number, html: string | JQuery, title: string | null) {
				this.id		= id;

				/* Elements */
				this.$instance = $('<div/>', {class: 'instance'});
				let $space = $('<div/>', {class: 'space'});
				let $window = $('<div/>', {class: 'window'});
				let $header = $('<div/>', {class: 'header'});
				let $title = $('<div/>', {class: 'title'});
				let $close = $('<div/>', {class: 'close'});
				let $main = $('<div/>', {class: 'main'});
				let $footer = $('<div/>', {class: 'footer'});

				/* Building DOM */
				Window.$windows.append(
					this.$instance.append(
						$space,
						$window.append(
							$header.append(
								$title,
								$close
							),
							$main.append(html),
							$footer
						)
					)
				);

				if (title !== null) $title.text(title);
				$window.addClass((title !== null) ? 'fill_title' : 'empty_title');

				/* Events */
				$space.on('click', this.Close.bind(this));
				$close.on('click', this.Close.bind(this));
			}

			Close(): void {
				this.Remove();
			}

			private Remove(): void {
				this.$instance.remove();
				Window.Delete(this.id);
			}

		}

	}
}