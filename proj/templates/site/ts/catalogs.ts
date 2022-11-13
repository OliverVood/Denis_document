namespace Site {
	export namespace Catalogs {

		export class  PriceList {
			/* Variables */

			/* Elements */
			$parent					: JQuery;
			$wrap					: JQuery;
			$header					: JQuery;
			$caption				: JQuery;
			$contacts				: JQuery;
			$contact_name			: JQuery;
			$contact_address		: JQuery;
			$contact_email			: JQuery;
			$contact_phone			: JQuery;
			$tables					: JQuery;

			constructor(selector) {
				/* Set elements */
				this.$parent 				= $(selector);
				this.$wrap					= $('<div/>', {class: 'wrap'});
				this.$header				= $('<div/>', {class: 'header'});
				this.$caption				= $('<div/>', {class: 'caption'});
				this.$contacts				= $('<div/>', {class: 'contacts'});
				this.$contact_name			= $('<input/>', {type: 'text', placeholder: 'Компания или Ф.И.О ...🖊'});
				this.$contact_address		= $('<input/>', {type: 'text', placeholder: 'Адрес ...🖊'});
				this.$contact_email			= $('<input/>', {type: 'text', placeholder: 'E-mail ...🖊'});
				this.$contact_phone			= $('<input/>', {type: 'text', placeholder: 'Телефон ...🖊'});
				this.$tables				= $('<div/>', {class: 'tables'});

				/* Events */

				/* Building DOM */
				this.$wrap.append(
					this.$header.append(
						this.$caption.text('Прайс-лист'),
						this.$contacts.append(
							$('<div/>').append(this.$contact_name),
							$('<div/>').append(this.$contact_address),
							$('<div/>').append(this.$contact_email),
							$('<div/>').append(this.$contact_phone)
						)
					),
					this.$tables,
					$('<div/>', {class: 'footer'}).append(
						$('<div/>').text('место для печати'),
						$('<div/>').append(
							$('<div/>').append(
								$('<div/>').text('Дата:')
							),
							$('<div/>').append(
								$('<div/>').text('Автограф:')
							),
						)
					)
				);
				this.$parent.append(
					this.$wrap
				);

				let table = new Table();
				this.$tables.append(
					table.GetTable()
				);
			}

		}

		class Table {
			/* Variables */
			iter					: number;

			/* Elements */
			$lines					: {[key: number]: JQuery};
			$table					: JQuery;
			$thead					: JQuery;
			$remove					: JQuery;
			$tbody					: JQuery;
			$add_line				: JQuery;
			$tr_sum					: JQuery;
			$tr_percent				: JQuery;
			$tr_total				: JQuery;

			constructor() {
				/* Set variables */
				this.iter = 0;

				/* Set elements */
				this.$lines 				= [];
				this.$table 				= $('<table/>');
				this.$thead 				= $('<thead/>');
				this.$remove 				= $('<span/>');
				this.$tbody 				= $('<tbody/>');
				this.$add_line 				= $('<span/>');
				this.$tr_sum 				= $('<tr/>', {class: 'sum'});
				this.$tr_percent 			= $('<tr/>', {class: 'percent'});
				this.$tr_total 				= $('<tr/>', {class: 'total'});


					this.$table.append(
						this.$thead.append(
							$('<tr/>').append(
								$('<th/>').append(
									this.$remove.text('+/-')
								),
								$('<th/>').text('Наименование'),
								$('<th/>').text('Количество'),
								$('<th/>').text('Еденица измерения'),
								$('<th/>').text('Цена'),
								$('<th/>').text('Сумма')
							)
						),
						this.$tbody.append(
							this.$tr_sum.append(
								$('<td/>').append(
									this.$add_line.text('+')
								),
								$('<td/>', {colspan: 3}),
								$('<td/>').text('Всего'),
								$('<td/>'),
							),
							this.$tr_percent.append(
								$('<td/>', {colspan: 4}),
								$('<td/>').text('Скидка, %'),
								$('<td/>').append(
									$('<input/>', {type: 'text', placeholder: '...🖊'})
								),
							),
							this.$tr_total.append(
								$('<td/>', {colspan: 4}),
								$('<td/>').text('Итого'),
								$('<td/>'),
							)
						)
					);

				this.Add();
				this.Add();
				this.Add();
				this.Add();

				/* Events */
				this.$remove.on('click', this.Remove.bind(this));
				this.$add_line.on('click', this.Add.bind(this));
			}

			public GetTable(): JQuery {
				return this.$table;
			}

			private Remove(): void {
				// this.$wrap.remove();
			}

			private Add(): void {
				/* Elements */
				let $remove = $('<span/>');
				let $count = $('<input/>', {type: 'text', placeholder: '...🖊'});
				let $price = $('<input/>', {type: 'text', placeholder: '...🖊'});
				let $sum = $('<span/>');

				/* Building DOM */
				let $tr = $('<tr/>', {class: 'line'}).append(
					$('<td/>').append(
						$remove.text('-')
					),
					$('<td/>').append(
						$('<input/>', {type: 'text', placeholder: '...🖊'})
					),
					$('<td/>').append(
						$count
					),
					$('<td/>').append(
						$('<input/>', {type: 'text', placeholder: '...🖊'})
					),
					$('<td/>').append(
						$price
					),
					$('<td/>').append(
						$sum
					)
				)
				this.$tr_sum.before($tr);

				/* Events */
				$remove.on('click', function() { $tr.remove(); });
				$count.on('blur', Sum.bind(this));
				$price.on('blur', Sum.bind(this));

				this.$lines[++this.iter] = $tr;

				function Sum() {
					console.log($count.val(), $price.val());
					let _su = Number($count.val()) * Number($price.val());
					$sum.text(_su);
				}
			}

		}

	}
}