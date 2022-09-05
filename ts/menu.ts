namespace UISite {

	export namespace Site {

		/**
		 * Управление меню
		 */
		export class Menu {
			jq_body			: JQuery;
			jq_wrap			: JQuery;
			jq_close		: JQuery;
			jq_menu_1		: JQuery;
			jq_menu_2		: JQuery;
			jq_menu_3		: JQuery;

			constructor() {
				/*  */
				this.jq_body = $('body');
				this.jq_wrap = $('<div/>', {class: 'view proj full_menu'});
				this.jq_close = $('<div/>', {class: 'close'});
				this.jq_menu_1 = $('<div/>', {class: 'menu m1'});
				this.jq_menu_2 = $('<div/>', {class: 'menu m2'});
				this.jq_menu_3 = $('<div/>', {class: 'menu m3'});

				/*  */
				this.jq_close.on('click', this.Close.bind(this));

				/*  */
				this.jq_wrap.append(
					this.jq_close,
					this.jq_menu_1.append(
						$('<div/>').append(
							$('<div/>').text('Личный кабинет'),
							$('<div/>').append(
								$('<div/>').text('Личные данные'),
								$('<div/>').text('Ещё что'),
								$('<div/>').text('Пустое меню'),
								$('<div/>').text('Выход')
							)
						)
					),
					this.jq_menu_2.append(
						$('<div/>').append(
							$('<div/>').text('Документы'),
							$('<div/>').append(
								$('<div/>').text('Управление товарами'),
								$('<div/>').text('Вава'),
								$('<div/>').text('Пустое меню'),
								$('<div/>').text('Выход')
							)
						)
					),
					this.jq_menu_3.append(
						$('<div/>').append(
							$('<div/>').text('Меню оки-доки'),
							$('<div/>').append(
								$('<div/>').text('Личные данные'),
								$('<div/>').text('Ещё что'),
								$('<div/>').text('Пустое меню'),
								$('<div/>').text('Выход')
							)
						)
					)
				);
			}

			Open() {
				console.log(123);
				this.jq_body.addClass('blur');
				this.jq_wrap.appendTo(this.jq_body);
			}

			Close() {
				this.jq_body.removeClass('blur');
				this.jq_wrap.detach();
			}
		}

	}

}