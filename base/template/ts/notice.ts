namespace Base {
	export namespace Common {

		type TypeNotice = 'ok' | 'error' | 'info' | 'common';

		export class Notice {
			/* Variables */
			private static iter = 0;
			private static notices = {};

			/* Elements */
			public static $notices = null;

			public static Create(type: TypeNotice, html: string): Instance {
				return Notice.New(type, html);
			}

			public static Ok(html: string | JQuery): Instance {
				return Notice.New('ok', html);
			}

			public static Info(html: string | JQuery): Instance {
				return Notice.New('info', html);
			}

			public static Error(html: string | JQuery): Instance {
				return Notice.New('error', html);
			}

			private static New(type: TypeNotice, html: string | JQuery): Instance {
				if (!Notice.$notices) {
					Notice.$notices = $('<div/>', {class: 'view general notices'});
					$('body').append(Notice.$notices);
				}

				Notice.iter++;
				let _wind = new Instance(Notice.iter, type, html);
				Notice.notices[Notice.iter] = _wind;

				return _wind;
			}

			public static Delete(id: number): void {
				delete Notice.notices[id];
			}

		}

		class Instance {
			/* Variables */
			id				: number;

			/* Elements */
			$instance		: JQuery;

			constructor(id: number, type: TypeNotice, html: string | JQuery) {
				this.id		= id;

				/* Elements */
				this.$instance = $('<div/>', {class: `instance ${type}`});
				let $notice = $('<div/>', {class: 'notice'});
				let $type = $('<div/>', {class: 'type'});
				let $close = $('<div/>', {class: 'close'});

				/* Building DOM */
				Notice.$notices.prepend(
					this.$instance.append(
						$type,
						$notice.append(html),
						$('<div/>', {class: 'close'}).append(
							$close
						)
					)
				);

				/* Events */
				$close.on('click', this.Close.bind(this));
			}

			Close(): void {
				this.Remove();
			}

			private Remove(): void {
				this.$instance.remove();
				Notice.Delete(this.id);
			}

		}

	}
}