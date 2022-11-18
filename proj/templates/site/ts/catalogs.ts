namespace Site {
	export namespace Catalogs {

		function DuplicateInit($elem: JQuery, event: string = 'input') {
			$elem.after(
				$('<span/>', {class: 'print'})
			);

			$elem.on(event, OnDuplicate);
		}

		function OnDuplicate(e) {
			let $source = $(e.currentTarget);
			$source.next().text($source.val().toString());
		}

		export class  Estimate {
			/* Variables */

			/* Elements */
			private $parent					: JQuery;
			private $wrap					: JQuery;
			private $header					: JQuery;
			private $caption				: JQuery;
			private $contacts				: JQuery;
			private $contact_name			: JQuery;
			private $contact_address		: JQuery;
			private $contact_email			: JQuery;
			private $contact_phone			: JQuery;
			private $lists					: JQuery;

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
				this.$lists					= $('<div/>', {class: 'lists'});

				/* Building DOM */
				this.$wrap.append(
					this.$header.append(
						this.$caption.text('Смета'),
						this.$contacts.append(
							$('<div/>').append(this.$contact_name),
							$('<div/>').append(this.$contact_address),
							$('<div/>').append(this.$contact_email),
							$('<div/>').append(this.$contact_phone)
						)
					),
					this.$lists,
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

				/* Duplicate */
				DuplicateInit(this.$contact_name);
				DuplicateInit(this.$contact_address);
				DuplicateInit(this.$contact_email);
				DuplicateInit(this.$contact_phone);

				this.AddList();

				this.$parent.append(this.$wrap);
			}

			private AddList() {
				let list = new List();
				this.$lists.append(
					list.GetElem()
				);
			}

		}

		class List {
			/* Variables */
			private items							: {[key: number]: Item};
			private iter							: number;
			private percent							: number;

			/* Elements */
			private $list							: JQuery;
			private $head							: JQuery;
			private $add_line						: JQuery;
			private $tr_sum							: JQuery;
			private $sum							: JQuery;
			private $percent						: JQuery;
			private $total							: JQuery;

			constructor() {
				/* Set variables */
				this.items 					= {};
				this.iter					= 0;
				this.percent				= 0;

				/* Set elements */
				this.$list 					= $('<div/>', {class: 'list'});
				this.$head	 				= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$add_line 				= $('<span/>');
				this.$tr_sum 				= $('<tr/>');
				this.$sum 					= $('<span/>');
				this.$percent				= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$total 				= $('<span/>');

				/* Events */
				this.$add_line.on('click', this.AddItem.bind(this));
				this.$percent.on('input', this.InputPercent.bind(this));
				this.$percent.on('blur', this.EnterPercent.bind(this));

				/* Building DOM */
				this.$list.append(
					$('<div/>', {class: 'title'}).append(this.$head),
					$('<table/>').append(
						$('<thead/>').append(
							$('<tr/>').append(
								$('<th/>').append($('<span/>').text('+/-')),
								$('<th/>').text('Наименование'),
								$('<th/>').text('Количество'),
								$('<th/>').text('Еденица измерения'),
								$('<th/>').text('Цена'),
								$('<th/>').text('Сумма')
							)
						),
						$('<tbody/>').append(
							this.$tr_sum.append(
								$('<td/>', {class: 'number'}).append(this.$add_line.text('+')),
								$('<td/>', {colspan: 3}),
								$('<td/>').text('Всего'),
								$('<td/>', {class: 'number'}).append(this.$sum),
							),
							$('<tr/>').append(
								$('<td/>'),
								$('<td/>', {colspan: 3}),
								$('<td/>').text('Скидка, %'),
								$('<td/>', {class: 'number'}).append(this.$percent),
							),
							$('<tr/>', {class: 'total'}).append(
								$('<td/>'),
								$('<td/>', {colspan: 3}),
								$('<td/>').text('Итого'),
								$('<td/>', {class: 'number'}).append(this.$total),
							)
						)
					)
				);

				/* Duplicate */
				DuplicateInit(this.$head);
				DuplicateInit(this.$percent, 'blur');

				this.AddItem();

				this.Sum();
			}

			public GetElem(): JQuery {
				return this.$list;
			}

			public AddItem(): void {
				let _id = ++this.iter;
				let item = new Item(_id, this);
				this.items[_id] = item;

				this.$tr_sum.before(item.GetElem());

				this.Sum();
			}

			public Sum(): void {
				let _sum = 0;
				for (let i in this.items) _sum += this.items[i].GetSum();

				this.$sum.text(_sum.toFixed(2));
				this.$total.text((_sum - (_sum * this.percent / 100)).toFixed(2));
			}

			private InputPercent(): void {
				this.percent = parseFloat(this.$percent.val().toString());
				if (isNaN(this.percent)) this.percent = 0;

				this.Sum();
			}

			private EnterPercent(): void {
				this.$percent.val(this.percent);
			}

			public RemoveItem(id: number): void {
				delete this.items[id];
				this.Sum();
			}

		}

		class Item {
			/* Variables */
			private list				: List;
			private id					: number;
			private sum					: number;

			/* Elements */
			private $tr					: JQuery;
			private $remove				: JQuery;
			private $name				: JQuery;
			private $count				: JQuery;
			private $unit				: JQuery;
			private $price				: JQuery;
			private $sum				: JQuery;

			constructor(id: number, table: List) {
				/* Set variables */
				this.list		= table;
				this.id			= id;
				this.sum		= 0;

				/* Set elements */
				this.$remove	= $('<span/>');

				this.$name		= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$count		= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$unit		= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$price		= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$sum		= $('<span/>');

				/* Events */
				this.$remove.on('click', this.Remove.bind(this));
				this.$count.on('input', this.Input.bind(this));
				this.$price.on('input', this.Input.bind(this));
				this.$count.on('blur', this.Enter.bind(this));
				this.$price.on('blur', this.Enter.bind(this));

				/* Building DOM */
				this.$tr = $('<tr/>', {class: 'line'}).append(
					$('<td/>', {class: 'number'}).append(this.$remove.text('-')),
					$('<td/>').append(this.$name, $('<span/>', {class: 'print'})),
					$('<td/>', {class: 'number'}).append(this.$count.val('0'), $('<span/>', {class: 'print'})),
					$('<td/>', {class: 'number'}).append(this.$unit, $('<span/>', {class: 'print'})),
					$('<td/>', {class: 'number'}).append(this.$price.val('0'), $('<span/>', {class: 'print'})),
					$('<td/>', {class: 'number'}).append(this.$sum)
				);

				/* Duplicate */
				DuplicateInit(this.$name);
				DuplicateInit(this.$unit);
				DuplicateInit(this.$count, 'blur');
				DuplicateInit(this.$price, 'blur');

				this.$sum.text(this.Sum());
			}

			public GetElem(): JQuery {
				return this.$tr;
			}

			public GetSum(): number {
				return this.sum;
			}

			private Sum(): number {
				let _price = Number(parseFloat(this.$price.val().toString()).toFixed(2));
				let _count = Number(parseFloat(this.$count.val().toString()).toFixed(2));
				if (isNaN(_count)) _count = 0;
				if (isNaN(_price)) _price = 0;

				return this.sum = Number((_price * _count).toFixed(2));
			}

			private Input(): void {
				this.$sum.text(this.Sum());
				this.list.Sum();
			}

			private Enter(e): void {
				let $input = $(e.currentTarget);

				let val = Number(parseFloat($input.val().toString()).toFixed(2));
				if (isNaN(val)) val = 0;

				$input.val(val);
			}

			private Remove(): void {
				this.list.RemoveItem(this.id);
				this.$tr.remove();
			}

		}

	}
}