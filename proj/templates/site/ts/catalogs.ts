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

		function GetDate(): string {
			let _date = new Date();
			return _date.toLocaleString('ru-RU', {year: 'numeric', month: 'numeric', day: 'numeric', hour: 'numeric', minute: 'numeric'});
		}

		export class Controller {
			/* Variables */
			static readonly STATE_EDIT				= 1;
			static readonly STATE_SAVE				= 2;
			private estimate						: Estimate;

			/* Elements */
			private readonly $view					: JQuery;
			private readonly $control				: JQuery;
			private readonly $btns					: JQuery;
			private readonly $info					: JQuery;
			private readonly $state					: JQuery;
			private readonly $list					: JQuery;
			private readonly $optgroup_old			: JQuery;
			private readonly btn_add				: JQuery;
			private readonly btn_print				: JQuery;
			private readonly $container				: JQuery;

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

				this.estimate = new Estimate(Number(this.$list.val()), this.$container, this);

				this.btn_add.removeAttr('disabled');
				this.btn_print.removeAttr('disabled');

				this.btn_add.off('click.estimate').on('click.estimate', () => this.estimate.AddTable(0));
				this.btn_print.off('click.estimate').on('click.estimate', () => window.print());
			}

			public SaveState(state: number) {
				let _class = '';
				let _text = '';
				switch (state) {
					case Controller.STATE_EDIT: _class = 'edit'; _text = 'Изменено'; break;
					case Controller.STATE_SAVE: _class = 'save'; _text = 'Сохранено'; break;
				}
				this.$state.removeClass().addClass(_class).text(_text);
			}

		}

		class Estimate {
			/* Variables */
			private id								: number;
			private datecr							: string;
			private datemd							: string;

			private company							: string;
			private address							: string;
			private phone							: string;
			private mail							: string;
			private date							: string;

			private readonly controller				: Controller;
			private readonly autosave				: number;
			private readonly tables					: {[key: number]: Table};
			private timer							?: number;

			/* Elements */
			private readonly $parent				: JQuery;
			private readonly $wrap					: JQuery;
			private readonly $header				: JQuery;
			private readonly $caption				: JQuery;
			private readonly $contacts				: JQuery;
			private readonly $contact_name			: JQuery;
			private readonly $contact_address		: JQuery;
			private readonly $contact_email			: JQuery;
			private readonly $contact_phone			: JQuery;
			private readonly $contact_date			: JQuery;
			private readonly $lists					: JQuery;

			constructor(id: number, $content: JQuery, controller: Controller) {
				/* Set variables */
				this.id						= id;

				this.controller				= controller;
				this.timer					= null;
				this.autosave				= 2000;
				this.tables 				= {};

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
				this.$contact_date			= $('<input/>', {type: 'date', class: 'number'});
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
									this.$contact_date
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
				DuplicateInit(this.$contact_date);

				this.$parent.append(this.$wrap);

				if (!this.id) {
					this.CreateData(Number(localStorage.getItem('EstimateIter')) || 1, '', '', '', '', Site.Common.UIDate.Today(), true, true);
					localStorage.setItem('EstimateIter', (this.id + 1).toString());

					this.Save();
					this.Fill();
					this.AutosaveEnable();
				} else {
					Site.Common.DB.Connect().then((result: IDBDatabase) => {
						let transactionEstimate = result.transaction('estimate', 'readonly');
						let storeEstimate = transactionEstimate.objectStore('estimate');
						let requestEstimate = storeEstimate.get(this.id);

						requestEstimate.onsuccess = (event) => {
							let result = event.target.result;
							this.CreateData(result.id, result.company, result.address, result.mail, result.phone, result.date, result.datecr, result.datemd);
							this.Fill();
							this.AutosaveEnable();
						}

						let transactionTable = result.transaction('estimate_table', 'readonly');
						let storeTable = transactionTable.objectStore('estimate_table');
						let estimateIndex = storeTable.index('eid');
						let requestTable = estimateIndex.openCursor(IDBKeyRange.only(this.id));

						requestTable.onsuccess = (event) => {
							let cursor = event.target.result;

							if (!cursor) return;
							this.AddTable(cursor.primaryKey, cursor.value);
							cursor.continue();
						}
					});
				}
			}

			public AddTable(id: number, data: TypeTableData | null = null) {
				this.tables[id] = new Table(id, this.id, data, this.$lists, this.controller, this);

				// this.Sum();
			}

			public RemoveTable(id: number): void {
				delete this.tables[id];

				// this.Sum();
			}

			private Fill() {
				this.$contact_name.val(this.company).trigger('input');
				this.$contact_address.val(this.address).trigger('input');
				this.$contact_email.val(this.mail).trigger('input');
				this.$contact_phone.val(this.phone).trigger('input');
				this.$contact_date.val(this.date).trigger('input');
			}

			private AutosaveEnable() {
				this.$contact_name.on('input', this.Commit.bind(this));
				this.$contact_address.on('input', this.Commit.bind(this));
				this.$contact_email.on('input', this.Commit.bind(this));
				this.$contact_phone.on('input', this.Commit.bind(this));
				this.$contact_date.on('input', this.Commit.bind(this));
			}

			private CreateData(id: number, company: string, address: string, mail: string, phone: string, date: string, datecr: string | boolean = false, datemd: string | boolean = false) {
				this.id = id;
				if (datecr) this.datecr = (datecr === true) ? GetDate() : datecr;

				this.UpdateData(company, address, mail, phone, date, datemd);
			}

			private UpdateData(company: string, address: string, mail: string, phone: string, date: string, datemd: string | boolean = false) {
				if (datemd) this.datemd = (datemd === true) ? GetDate() : datemd;

				this.company = company;
				this.address = address;
				this.mail = mail;
				this.phone = phone;
				this.date = date;
			}

			private Commit() {
				clearTimeout(this.timer);
				this.timer = setTimeout(this.UpdateDataAndSave.bind(this), this.autosave);
				this.controller.SaveState(Controller.STATE_EDIT);
			}

			private UpdateDataAndSave() {
				this.UpdateData(
					this.$contact_name.val().toString(),
					this.$contact_address.val().toString(),
					this.$contact_email.val().toString(),
					this.$contact_phone.val().toString(),
					this.$contact_date.val().toString(),
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
						mail: this.mail,
						phone: this.phone,
						date: this.date
					};

					store.put(data);
					this.controller.SaveState(Controller.STATE_SAVE);
				});
			}

		}

		type TypeTableData = { id: number, eid: number, datecr: string, datemd : string, header: string, discount: number  };

		class Table {
			/* Variables */
			private id								: number;
			private eid								: number;
			private datecr							: string;
			private datemd							: string;

			private header							: string;
			private discount						: number;

			private readonly controller				: Controller;
			private readonly estimate				: Estimate;
			private readonly autosave				: number;
			private timer							?: number;



			private items							: {[key: number]: Item};
			private iter							: number;
			private collapse						: boolean;
			private visible							: boolean;

			/* Elements */
			private readonly $container				: JQuery;
			private readonly $list					: JQuery;
			private readonly $wrap					: JQuery;
			private readonly $header				: JQuery;
			private readonly $visible				: JQuery;
			private readonly $delete				: JQuery;
			private readonly $table					: JQuery;
			private readonly $add_line				: JQuery;
			private readonly $collapse				: JQuery;
			private readonly $tr_sum				: JQuery;
			private readonly $sum					: JQuery;
			private readonly $discount				: JQuery;
			private readonly $total					: JQuery;

			constructor(id: number, eid: number, data: TypeTableData | null, $container: JQuery, controller: Controller, estimate: Estimate) {
				/* Set variables */
				this.id						= id;
				this.eid					= eid;

				this.controller				= controller;
				this.estimate				= estimate;
				this.timer					= null;
				this.autosave				= 2000;



				this.items 					= {};
				this.iter					= 0;
				this.collapse				= false;
				this.visible				= true;

				/* Set elements */
				this.$container 			= $container;
				this.$list 					= $('<div/>', {class: 'list'});
				this.$wrap					= $('<div/>', {class: 'wrap'});
				this.$header	 			= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$collapse				= $('<span/>', {class: 'item collapse', title: "Свернуть строки"});
				this.$visible				= $('<span/>', {class: 'visible', title: "Скрыть таблицу"});
				this.$delete				= $('<span/>', {class: 'delete negative', title: "Удалить таблицу"});
				this.$add_line 				= $('<span/>', {class: 'item add', title: 'Добавить строку'});
				this.$table					= $('<table/>');
				this.$tr_sum 				= $('<tr/>');
				this.$sum 					= $('<span/>');
				this.$discount				= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$total 				= $('<span/>');

				/* Events */
				// this.$add_line.on('click', this.AddItem.bind(this));
				// this.$collapse.on('click', this.OnCollapse.bind(this));
				// this.$visible.on('click', this.OnVisible.bind(this));
				this.$delete.on('click', this.Remove.bind(this));

				/* Building DOM */
				this.$list.append(
					$('<div/>', {class: 'control glob_tabu'}).append(
						this.$visible,
						this.$delete
					),
					this.$wrap.append(
						$('<div/>', {class: 'title'}).append(this.$header),
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
									$('<td/>', {class: 'number'}).append(this.$discount),
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
				DuplicateInit(this.$header);
				DuplicateInit(this.$discount, 'blur');

				this.$container.append(this.$list);

				if (!this.id) {
					this.CreateData(Number(localStorage.getItem('EstimateTableIter')) || 1, '', 0, true, true);
					localStorage.setItem('EstimateTableIter', (this.id + 1).toString());

					this.Save();
					this.$discount.on('blur', this.EnterPercent.bind(this));
				} else {
					this.CreateData(data.id, data.header, data.discount, data.datecr, data.datemd);
				}

				this.Fill();
				this.AutosaveEnable();

				// this.AddItem();
				//
				// this.Sum();
			}

			private Fill() {
				this.$header.val(this.header).trigger('input');
				this.$discount.val(this.discount).trigger('blur');
			}

			private AutosaveEnable() {
				this.$header.on('input', this.Commit.bind(this));
				this.$discount.on('input', this.Commit.bind(this));
			}

			CreateData(id: number, header: string, discount: number, datecr: string | boolean = false, datemd: string | boolean = false) {
				this.id = id;
				if (datecr) this.datecr = (datecr === true) ? GetDate() : datecr;

				this.UpdateData(header, discount, datemd);
			}

			UpdateData(header: string, discount: number, datemd: string | boolean = false) {
				if (datemd) this.datemd = (datemd === true) ? GetDate() : datemd;

				this.header = header;
				this.discount = discount;
			}

			private Commit() {
				clearTimeout(this.timer);
				this.timer = setTimeout(this.UpdateDataAndSave.bind(this), this.autosave);
				this.controller.SaveState(Controller.STATE_EDIT);
			}

			private UpdateDataAndSave() {
				this.UpdateData(
					this.$header.val().toString(),
					this.GetDiscount(),
					true
				);
				this.Save();
			}

			private Save() {
				Site.Common.DB.Connect().then((result: IDBDatabase) => {
					let transaction = result.transaction('estimate_table', 'readwrite');
					let store = transaction.objectStore('estimate_table');
					let data = {
						id: this.id,
						eid: this.eid,
						datecr: this.datecr,
						datemd: this.datemd,

						header: this.header,
						discount: this.discount
					};

					store.put(data);
					this.controller.SaveState(Controller.STATE_SAVE);
				});
			}

			private GetDiscount(): number {
				let discount = parseFloat(this.$discount.val().toString());
				if (isNaN(this.discount)) discount = 0;

				return discount
			}

			private EnterPercent(): void {
				this.$discount.val(this.GetDiscount());
			}

			private Remove(): void {
				Site.Common.DB.Connect().then((result: IDBDatabase) => {
					let transaction = result.transaction('estimate_table', 'readwrite');
					let store = transaction.objectStore('estimate_table');
					store.delete(this.id);
				});

				this.estimate.RemoveTable(this.id);
				this.$list.remove();
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
				this.$total.text((_sum - (_sum * this.discount / 100)).toFixed(2));
			}

			public RemoveItem(id: number): void {
				delete this.items[id];
				this.Sum();
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