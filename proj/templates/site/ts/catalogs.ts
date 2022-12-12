namespace Site {
	export namespace Catalogs {

		function DuplicateInit($elem: JQuery, event: string = 'input') {
			$elem.after(
				$('<span/>', {class: 'glob_print'})
			);

			$elem.on(event, OnDuplicate);
		}

		function OnDuplicate(e) {
			let $source = $(e.currentTarget);
			$source.next().text($source.val().toString());
		}

		export class Controller {
			// const STATE_EDIT				= 1;

			/* Variables */
			private estimate				: Estimate;

			/* Elements */
			$view							: JQuery;
			$control						: JQuery;
			$btns							: JQuery;
			$info							: JQuery;
			$state							: JQuery;
			$list							: JQuery;
			$optgroup_old					: JQuery;
			btn_add							: JQuery;
			btn_print						: JQuery;
			$container						: JQuery;

			constructor(selector: string) {
				/* Set elements */
				this.$view = $(selector);
				this.$control = $('<div/>', {class: 'control glob_tabu'});
				this.$btns = $('<div/>', {class: 'btns'});
				this.$info = $('<div/>', {class: 'info'});
				this.$state = $('<span/>', {class: 'state'});
				this.$list = $('<select/>');
				this.$optgroup_old = $('<optgroup/>', {label: 'Сохранённые сметы:'});
				this.btn_add = $('<input/>', {type: 'button', value: 'Добавить таблицу', disabled: true, class: 'img add_table'});
				this.btn_print = $('<input/>', {type: 'button', value: 'Печать', disabled: true, class: 'img print'});
				this.$container = $('<div/>', {class: 'container'});

				/* Building DOM */
				this.$view.append(
					this.$control.append(
						this.$btns.append(
							this.$list.append(
								$('<option/>', {value: '', selected: true, disabled: true, hidden: true}).text('Выберите смету'),
								$('<optgroup/>', {label: 'Действие:'}).append(
									$('<option/>', {value: '0'}).text('Создать новую')
								)
							),
							this.btn_add,
							this.btn_print
						),
						this.$info.append(
							this.$state
						)
					),
					this.$container
				);

				Site.Common.DB.Cursor('estimate', (cursor) => {
					if (!cursor) return;

					let key = cursor.key;
					let value = cursor.value;

					this.$optgroup_old.append(
						$('<option/>', {value: key}).text(`Изменено ${value.datemd} (от ${value.datecr})`)
					);
					this.$list.append(this.$optgroup_old);

					cursor.continue();
				});

				/* Events */
				this.$list.on('change', this.CreateEstimate.bind(this));
			}

			private CreateEstimate() {
				this.$container.empty();

				this.estimate = new Estimate(Number(this.$list.val()), this.$container);

				this.btn_add.removeAttr('disabled');
				this.btn_print.removeAttr('disabled');

				this.btn_add.off('click.doc').on('click.doc', () => this.estimate.AddList());
				this.btn_print.off('click.doc').on('click.doc', () => window.print());
			}

			public SaveState(state: string) {

			}

		}

		class Estimate {
			/* Variables */
			private id						: number;
			private datecr					: string;
			private datemd					: string;
			private company					: string;
			private address					: string;
			private phone					: string;
			private mail					: string;
			private timer					?: number;
			private autosave				: number;

			private iter					: number;
			private lists					: {[key: number]: Table};
			private dataOptions;

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

			constructor(id: number, $content: JQuery) {
				/* Set variables */
				this.id						= id;
				this.timer					= null;
				this.autosave				= 2000;
				this.iter 					= 0//Number(localStorage.getItem('EstimateTableIter'));
				this.lists 					= {};
				this.dataOptions 			= {
					year: 'numeric',
					month: 'numeric',
					day: 'numeric',
					hour: 'numeric',
					minute: 'numeric'
				};

				/* Set elements */
				this.$parent 				= $content;
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
							$('<div/>', {class: 'date'}).append(
								$('<div/>').text('Дата:'),
								$('<div/>').append(
									$('<input/>', {type: 'date', value: Site.Common.UIDate.Today(), class: 'number'})
								)
							),
							$('<div/>', {class: 'autograph'}).append(
								$('<div/>').text('Автограф:'),
								$('<div/>').append(
									$('<div/>')
								)
							),
						)
					)
				);

				/* Duplicate */
				DuplicateInit(this.$contact_name);
				DuplicateInit(this.$contact_address);
				DuplicateInit(this.$contact_email);
				DuplicateInit(this.$contact_phone);

				this.$parent.append(this.$wrap);

				if (!this.id) {
					this.CreateData(Number(localStorage.getItem('EstimateIter')) || 1, '', '', '', '', true, true);
					localStorage.setItem('EstimateIter', (this.id + 1).toString());

					this.Save();
					this.AutosaveEnable();
				} else {
					Site.Common.DB.Connect().then((result: IDBDatabase) => {
						let transaction = result.transaction('estimate', 'readonly');
						let store = transaction.objectStore('estimate');
						let request = store.get(this.id);

						request.onsuccess = (event) => {
							let result = event.target.result;
							this.CreateData(result.id, result.company, result.address, result.phone, result.mail, result.datecr, result.datemd);
							this.Fill();
							this.AutosaveEnable();
						}
					});
				}
			}

			public RemoveList(id: number): void {
				delete this.lists[id];

				// this.Sum();
			}

			public AddList() {
				let _id = ++this.iter;
				let _table = new Table(_id, this);

				// localStorage.setItem('EstimateIter', _id.toString());
				this.lists[_id] = _table;

				this.$lists.append(
					_table.GetElem()
				);

				// this.Sum();
			}

			private Fill() {
				this.$contact_name.val(this.company).trigger('input');
				this.$contact_address.val(this.address).trigger('input');
				this.$contact_phone.val(this.phone).trigger('input');
				this.$contact_email.val(this.mail).trigger('input');
			}

			private AutosaveEnable() {
				this.$contact_name.on('input', this.Commit.bind(this));
				this.$contact_address.on('input', this.Commit.bind(this));
				this.$contact_email.on('input', this.Commit.bind(this));
				this.$contact_phone.on('input', this.Commit.bind(this));
			}

			private CreateData(id: number, company: string, address: string, phone: string, mail: string, datecr: string | boolean = false, datemd: string | boolean = false) {
				this.id = id;

				this.UpdateData(company, address, phone, mail, datecr, datemd);
			}

			private UpdateData(company: string, address: string, phone: string, mail: string, datecr: string | boolean = false, datemd: string | boolean = false) {
				let date = new Date();
				let date_str = date.toLocaleString('ru', this.dataOptions);

				if (datecr) this.datecr = (datecr === true) ? date_str : datecr;
				if (datemd) this.datemd = (datemd === true) ? date_str : datemd;
				this.company = company;
				this.address = address;
				this.phone = phone;
				this.mail = mail;
			}

			private Commit() {
				clearTimeout(this.timer);
				this.timer = setTimeout(this.UpdateDataAndSave.bind(this), this.autosave);
			}

			private UpdateDataAndSave() {
				this.UpdateData(
					this.$contact_name.val().toString(),
					this.$contact_address.val().toString(),
					this.$contact_phone.val().toString(),
					this.$contact_email.val().toString(),
					false,
					true
				);
				this.Save();
			}

			private Save() {
				Site.Common.DB.Connect().then((result: IDBDatabase) => {
					let transaction = result.transaction('estimate', 'readwrite');
					let store = transaction.objectStore('estimate');
					let data = {
						id: this.id,
						datecr: this.datecr,
						datemd: this.datemd,
						company: this.company,
						address: this.address,
						phone: this.phone,
						mail: this.mail
					};

					store.put(data);
				});
			}

		}

		class Table {

			// 	let transaction = this.db.result.transaction('estimate', 'readwrite');
			// 	let store = transaction.objectStore('estimate');
			// 	let estimate = {
			// 		company: 'ИП Иванов Ю. И.',
			// 		address: 'ул. Нахимова, 28',
			// 		mail: 'ivanov_master@mail.ru',
			// 		phone: '+7 (923) 500 11 11',
			// 		// id: this.id
			// 		// datecr: new Date()
			// 		// datemd: new Date()
			// 		id: 4,
			// 		datecr: '02.12.2022, 19:29',
			// 		datemd: '03.12.2022, 19:45'
			// 	};
			// 	// let request = store.put(estimate);
			//
			// 	// let datemd = new Date();
			// 	// console.log(datemd.toLocaleString('ru', {
			// 	// 	year: 'numeric',
			// 	// 	month: 'numeric',
			// 	// 	day: 'numeric',
			// 	// 	hour: 'numeric',
			// 	// 	minute: 'numeric'
			// 	// }));
			//
			// 	this.AddList();
			/* Variables */
			private estimate						: Estimate;
			private id								: number;
			private items							: {[key: number]: Item};
			private iter							: number;
			private percent							: number;
			private collapse						: boolean;
			private visible							: boolean;

			/* Elements */
			private $list							: JQuery;
			private $wrap							: JQuery;
			private $head							: JQuery;
			private $visible						: JQuery;
			private $delete							: JQuery;
			private $table							: JQuery;
			private $add_line						: JQuery;
			private $collapse						: JQuery;
			private $tr_sum							: JQuery;
			private $sum							: JQuery;
			private $percent						: JQuery;
			private $total							: JQuery;

			constructor(id: number, estimate: Estimate) {
				/* Set variables */
				this.estimate				= estimate;
				this.id						= id;
				this.items 					= {};
				this.iter					= 0;
				this.percent				= 0;
				this.collapse				= false;
				this.visible				= true;

				/* Set elements */
				this.$list 					= $('<div/>', {class: 'list'});
				this.$wrap					= $('<div/>', {class: 'wrap'});
				this.$head	 				= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$collapse				= $('<span/>', {class: 'item collapse', title: "Свернуть строки"});
				this.$visible				= $('<span/>', {class: 'visible', title: "Скрыть таблицу"});
				this.$delete				= $('<span/>', {class: 'delete negative', title: "Удалить таблицу"});
				this.$add_line 				= $('<span/>', {class: 'item add', title: 'Добавить строку'});
				this.$table					= $('<table/>');
				this.$tr_sum 				= $('<tr/>');
				this.$sum 					= $('<span/>');
				this.$percent				= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$total 				= $('<span/>');

				/* Events */
				this.$add_line.on('click', this.AddItem.bind(this));
				this.$percent.on('input', this.InputPercent.bind(this));
				this.$percent.on('blur', this.EnterPercent.bind(this));
				this.$collapse.on('click', this.OnCollapse.bind(this));
				this.$visible.on('click', this.OnVisible.bind(this));
				this.$delete.on('click', this.OnDelete.bind(this));

				/* Building DOM */
				this.$list.append(
					$('<div/>', {class: 'control glob_tabu'}).append(
						this.$visible,
						this.$delete
					),
					this.$wrap.append(
						$('<div/>', {class: 'title'}).append(this.$head),
						this.$table.append(
							$('<thead/>').append(
								$('<tr/>').append(
									$('<th/>', {class: 'glob_tabu'}).append($('<span/>').text('+/-')),
									$('<th/>').text('Наименование'),
									$('<th/>').text('Количество'),
									$('<th/>').text('Единица измерения'),
									$('<th/>').text('Цена'),
									$('<th/>').text('Сумма')
								)
							),
							$('<tbody/>').append(
								this.$tr_sum.append(
									$('<td/>', {class: 'number glob_tabu'}).append(this.$add_line),
									$('<td/>', {colspan: 3}),
									$('<td/>').text('Всего'),
									$('<td/>', {class: 'number'}).append(this.$sum),
								),
								$('<tr/>').append(
									$('<td/>', {class: 'number glob_tabu'}).append(
										this.$collapse
									),
									$('<td/>', {colspan: 3}),
									$('<td/>').text('Скидка, %'),
									$('<td/>', {class: 'number'}).append(this.$percent),
								),
								$('<tr/>', {class: 'total'}).append(
									$('<td/>', {class: 'glob_tabu'}),
									$('<td/>', {colspan: 3}),
									$('<td/>').text('Итого'),
									$('<td/>', {class: 'number'}).append(this.$total),
								)
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

			public RemoveItem(id: number): void {
				delete this.items[id];
				this.Sum();
			}

			private InputPercent(): void {
				this.percent = parseFloat(this.$percent.val().toString());
				if (isNaN(this.percent)) this.percent = 0;

				this.Sum();
			}

			private EnterPercent(): void {
				this.$percent.val(this.percent);
			}

			private OnCollapse(): void {
				this.collapse = !this.collapse;

				if (this.collapse) {
					this.$table.find('tr.line').addClass('glob_print');
					this.$add_line.addClass('glob_hide');
				} else {
					this.$table.find('tr.line').removeClass('glob_print');
					this.$add_line.removeClass('glob_hide');
				}
			}

			private OnVisible(): void {
				this.visible = !this.visible;

				if (this.visible) this.$wrap.removeClass('glob_hide');
				else this.$wrap.addClass('glob_hide');
			}

			private OnDelete(): void {
				this.Remove();
			}

			private Remove(): void {
				this.estimate.RemoveList(this.id);
				this.$list.remove();
			}

		}

		class Item {
			/* Variables */
			private list				: Table;
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

			constructor(id: number, list: Table) {
				/* Set variables */
				this.list		= list;
				this.id			= id;
				this.sum		= 0;

				/* Set elements */
				this.$remove	= $('<span/>', {class: 'item del negative', title: 'Удалить строку'});

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
					$('<td/>', {class: 'number glob_tabu'}).append(this.$remove),
					$('<td/>').append(this.$name, $('<span/>', {class: 'glob_print'})),
					$('<td/>', {class: 'number'}).append(this.$count.val('0')),
					$('<td/>', {class: 'number'}).append(this.$unit),
					$('<td/>', {class: 'number'}).append(this.$price.val('0')),
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
				let _price = +(parseFloat(this.$price.val().toString()).toFixed(2));
				let _count = +(parseFloat(this.$count.val().toString()).toFixed(2));
				if (isNaN(_count)) _count = 0;
				if (isNaN(_price)) _price = 0;

				return this.sum = +((_price * _count).toFixed(2));
			}

			private Input(): void {
				this.$sum.text(this.Sum());
				this.list.Sum();
			}

			private Enter(e): void {
				let $input = $(e.currentTarget);

				let val = +(parseFloat($input.val().toString()).toFixed(2));
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