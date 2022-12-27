namespace Site {
	export namespace Catalogs {

		function DuplicateInit($elem: JQuery, event: string = 'input'): void {
			$elem.after(
				$('<span/>', {class: 'glob_print'})
			);

			$elem.on(event, OnDuplicate);
		}

		function OnDuplicate(e): void {
			let $source = $(e.currentTarget);
			$source.next().text($source.val().toString());
		}

		function GetDate(): string {
			let _date = new Date();
			return _date.toLocaleString('ru-RU', {year: 'numeric', month: 'numeric', day: 'numeric', hour: 'numeric', minute: 'numeric'});
		}

		function EmptyIfZero(th): void {
			let $th = $(th.currentTarget);
			if ($th.val() === '0') $th.val('');
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
			private readonly $btn_new				: JQuery;
			private readonly $select				: JQuery;
			private readonly btn_add				: JQuery;
			private readonly btn_print				: JQuery;
			private readonly $container				: JQuery;

			constructor(selector: string) {
				/* Set elements */
				this.$view = $(selector);
				this.$control = $('<div/>', {class: 'control glob_tabu'});
				this.$btns = $('<div/>', {class: 'btns'});
				this.$btn_new = $('<input/>', {type: 'button', class: 'img new', value: 'Новая'});
				this.$select = $('<select/>');
				this.btn_add = $('<input/>', {type: 'button', value: 'Добавить таблицу', disabled: true, class: 'img add_table'});
				this.btn_print = $('<input/>', {type: 'button', value: 'Печать', disabled: true, class: 'img print'});
				this.$info = $('<div/>', {class: 'info'});
				this.$state = $('<span/>', {class: 'state'});
				this.$container = $('<div/>', {class: 'container'});

				/* Building DOM */
				this.$view.append(
					this.$control.append(
						this.$btns.append(
							this.$btn_new,
							this.$select.append(
								$('<option/>', {value: '', selected: true, disabled: true, hidden: true}).text('Выберите смету')
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

				Site.Common.DB.Connect().then((result: IDBDatabase) => {
					Site.Common.DB.Cursor(result, 'estimate', cursor => {
						let key = cursor.key;
						let value = cursor.value;

						this.$select.append(
							$('<option/>', {value: key}).text(`Изменено ${value.datemd} (от ${value.datecr})`)
						);
					}, () => {
						new Skins.Select(this.$select, this.DeleteEstimate);
					});
				});

				/* Events */
				this.$btn_new.on('click', this.NewEstimate.bind(this))
				this.$select.on('change', this.CreateEstimate.bind(this));
			}

			private NewEstimate() {
				this.$container.empty();

				this.estimate = new Estimate(0, this.$container, this);

				this.btn_add.removeAttr('disabled');
				this.btn_print.removeAttr('disabled');

				this.btn_add.off('click.estimate').on('click.estimate', () => this.estimate.AddTable(0));
				this.btn_print.off('click.estimate').on('click.estimate', () => window.print());
			}

			private CreateEstimate() {
				this.$container.empty();

				this.estimate = new Estimate(Number(this.$select.val()), this.$container, this);

				this.btn_add.removeAttr('disabled');
				this.btn_print.removeAttr('disabled');

				this.btn_add.off('click.estimate').on('click.estimate', () => this.estimate.AddTable(0));
				this.btn_print.off('click.estimate').on('click.estimate', () => window.print());
			}

			private DeleteEstimate(id: number) {
				Site.Common.DB.Connect().then((db: IDBDatabase) => {
					Site.Common.DB.CursorIndex(db, 'estimate_table', 'eid', IDBKeyRange.only(id), cursor => {
						Site.Common.DB.CursorIndex(db, 'estimate_record', 'tid', IDBKeyRange.only(cursor.value.id), cursor => {
							Site.Common.DB.Delete(db, 'estimate_record', cursor.value.id);
						});
						Site.Common.DB.Delete(db, 'estimate_table', cursor.value.id);
					});
					Site.Common.DB.Delete(db, 'estimate', id);
				});
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
			private readonly tables					: {[key: number]: Table};
			private readonly autosave				: number;
			private timer							?: number;

			/* Elements */
			private readonly $container				: JQuery;
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

			constructor(id: number, $container: JQuery, controller: Controller) {
				/* Set variables */
				this.id								= id;

				this.controller						= controller;
				this.tables 						= {};
				this.timer							= null;
				this.autosave						= 2000;

				/* Set elements */
				this.$container 					= $container;
				this.$wrap							= $('<div/>', {class: 'wrap'});
				this.$header						= $('<div/>', {class: 'header'});
				this.$caption						= $('<div/>', {class: 'caption'});
				this.$contacts						= $('<div/>', {class: 'contacts'});
				this.$contact_name					= $('<input/>', {type: 'text', placeholder: 'Компания или Ф.И.О ...🖊'});
				this.$contact_address				= $('<input/>', {type: 'text', placeholder: 'Адрес ...🖊'});
				this.$contact_email					= $('<input/>', {type: 'text', placeholder: 'E-mail ...🖊'});
				this.$contact_phone					= $('<input/>', {type: 'text', placeholder: 'Телефон ...🖊'});
				this.$contact_date					= $('<input/>', {type: 'date', class: 'number'});
				this.$lists							= $('<div/>', {class: 'lists'});

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

				this.$container.append(this.$wrap);

				if (!this.id) {
					this.CreateData(Number(localStorage.getItem('EstimateIter')) || 1, '', '', '', '', Site.Common.UIDate.Today(), true, true);
					localStorage.setItem('EstimateIter', (this.id + 1).toString());

					this.Save();
					this.Fill();
					this.AutosaveEnable();
				} else {
					Site.Common.DB.Connect().then((db: IDBDatabase) => {
						Site.Common.DB.Get(db, 'estimate', this.id).then((result) => {
							this.CreateData(result.id, result.company, result.address, result.mail, result.phone, result.date, result.datecr, result.datemd);
							this.Fill();
							this.AutosaveEnable();
						});
						Site.Common.DB.CursorIndex(db, 'estimate_table', 'eid', IDBKeyRange.only(this.id), cursor => {
							this.AddTable(cursor.primaryKey, cursor.value);
						});
					});
				}
			}

			public AddTable(id: number, data: TypeTableData | null = null): void {
				this.tables[id] = new Table(id, this.id, data, this.$lists, this.controller, this);
			}

			public RemoveTable(id: number): void {
				delete this.tables[id];
			}

			private Fill(): void {
				this.$contact_name.val(this.company).trigger('input');
				this.$contact_address.val(this.address).trigger('input');
				this.$contact_email.val(this.mail).trigger('input');
				this.$contact_phone.val(this.phone).trigger('input');
				this.$contact_date.val(this.date).trigger('input');
			}

			private AutosaveEnable(): void {
				this.$contact_name.on('input', this.Commit.bind(this));
				this.$contact_address.on('input', this.Commit.bind(this));
				this.$contact_email.on('input', this.Commit.bind(this));
				this.$contact_phone.on('input', this.Commit.bind(this));
				this.$contact_date.on('input', this.Commit.bind(this));
			}

			private CreateData(id: number, company: string, address: string, mail: string, phone: string, date: string, datecr: string | boolean = false, datemd: string | boolean = false): void {
				this.id = id;
				if (datecr) this.datecr = (datecr === true) ? GetDate() : datecr;

				this.UpdateData(company, address, mail, phone, date, datemd);
			}

			private UpdateData(company: string, address: string, mail: string, phone: string, date: string, datemd: string | boolean = false): void {
				if (datemd) this.datemd = (datemd === true) ? GetDate() : datemd;

				this.company = company;
				this.address = address;
				this.mail = mail;
				this.phone = phone;
				this.date = date;
			}

			private Commit(): void {
				clearTimeout(this.timer);
				this.timer = setTimeout(this.UpdateDataAndSave.bind(this), this.autosave);
				this.controller.SaveState(Controller.STATE_EDIT);
			}

			private UpdateDataAndSave(): void {
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

			private Save(): void {
				Site.Common.DB.Connect().then((db: IDBDatabase) => {
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
					Site.Common.DB.Put(db, 'estimate', data);
					this.controller.SaveState(Controller.STATE_SAVE);
				});
			}

		}

		type TypeTableData = { id: number, eid: number, datecr: string, datemd : string, header: string, discount: number };

		class Table {
			/* Variables */
			private id								: number;
			private readonly eid					: number;
			private datecr							: string;
			private datemd							: string;

			private header							: string;
			private discount						: number;

			private sum								: number;

			private readonly controller				: Controller;
			private readonly estimate				: Estimate;
			private readonly records				: {[key: number]: Record};
			private readonly autosave				: number;
			private timer							?: number;
			private visible							: boolean;
			private collapse						: boolean;

			/* Elements */
			private readonly $container				: JQuery;
			private readonly $list					: JQuery;
			private readonly $wrap					: JQuery;
			private readonly $header				: JQuery;
			private readonly $visible				: JQuery;
			private readonly $remove				: JQuery;
			private readonly $table					: JQuery;
			private readonly $add_line				: JQuery;
			private readonly $collapse				: JQuery;
			private readonly $tr_sum				: JQuery;
			private readonly $sum					: JQuery;
			private readonly $discount				: JQuery;
			private readonly $total					: JQuery;

			constructor(id: number, eid: number, data: TypeTableData | null, $container: JQuery, controller: Controller, estimate: Estimate) {
				/* Set variables */
				this.id								= id;
				this.eid							= eid;

				this.sum							= 0;

				this.controller						= controller;
				this.estimate						= estimate;
				this.records 						= {};
				this.timer							= null;
				this.autosave						= 2000;
				this.collapse						= false;
				this.visible						= true;

				/* Set elements */
				this.$container 					= $container;
				this.$list 							= $('<div/>', {class: 'list'});
				this.$wrap							= $('<div/>', {class: 'wrap'});
				this.$header	 					= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$collapse						= $('<span/>', {class: 'item collapse', title: "Свернуть строки"});
				this.$visible						= $('<span/>', {class: 'visible', title: "Скрыть таблицу"});
				this.$remove						= $('<span/>', {class: 'delete negative', title: "Удалить таблицу"});
				this.$add_line 						= $('<span/>', {class: 'item add', title: 'Добавить строку'});
				this.$table							= $('<table/>');
				this.$tr_sum 						= $('<tr/>');
				this.$sum 							= $('<span/>');
				this.$discount						= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$total 						= $('<span/>');

				/* Events */
				this.$visible.on('click', this.Visible.bind(this));
				this.$remove.on('click', this.Remove.bind(this));
				this.$add_line.on('click', () => this.AddRecord(0));
				this.$collapse.on('click', this.CollapseRecords.bind(this));

				/* Building DOM */
				this.$list.append(
					$('<div/>', {class: 'control glob_tabu'}).append(
						this.$visible,
						this.$remove
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
				} else {
					this.CreateData(data.id, data.header, data.discount, data.datecr, data.datemd);

					Site.Common.DB.Connect().then((db: IDBDatabase) => {
						Site.Common.DB.CursorIndex(db, 'estimate_record', 'tid', IDBKeyRange.only(this.id), cursor => {
							this.AddRecord(cursor.primaryKey, cursor.value);
						}, () => {
							this.Sum();
						});
					});
				}

				this.$discount.on('focus', EmptyIfZero);
				this.$discount.on('input', this.Input.bind(this));
				this.$discount.on('blur', this.EnterPercent.bind(this));
				this.Fill();
				this.AutosaveEnable();
			}

			public Sum(): void {
				let sum = 0;
				for (let i in this.records) sum += this.records[i].GetSum();
				this.sum = (this.discount) ? Number((sum - (sum * this.discount / 100)).toFixed(2)) : sum;

				this.$total.text(this.sum);
			}

			private AddRecord(id: number, data: TypeRecordData | null = null): void {
				let _record = new Record(id, this.id, data, this.$tr_sum, this.controller, this);
				let _id = _record.GetId();
				this.records[_id] = _record;
			}

			public RemoveRecord(id: number): void {
				delete this.records[id];
				this.Sum();
			}

			private CollapseRecords(): void {
				this.collapse = !this.collapse;

				if (this.collapse) {
					this.$table.find('tr.line').addClass('glob_print');
					this.$add_line.addClass('glob_hide');
				} else {
					this.$table.find('tr.line').removeClass('glob_print');
					this.$add_line.removeClass('glob_hide');
				}
			}

			private Fill(): void {
				this.$header.val(this.header).trigger('input');
				this.$discount.val(this.discount).trigger('blur');
			}

			private AutosaveEnable(): void {
				this.$header.on('input', this.Commit.bind(this));
				this.$discount.on('input', this.Commit.bind(this));
			}

			private CreateData(id: number, header: string, discount: number, datecr: string | boolean = false, datemd: string | boolean = false): void {
				this.id = id;
				if (datecr) this.datecr = (datecr === true) ? GetDate() : datecr;

				this.UpdateData(header, discount, datemd);
			}

			private UpdateData(header: string, discount: number, datemd: string | boolean = false): void {
				if (datemd) this.datemd = (datemd === true) ? GetDate() : datemd;

				this.header = header;
				this.discount = discount;
			}

			private Commit(): void {
				clearTimeout(this.timer);
				this.timer = setTimeout(this.UpdateDataAndSave.bind(this), this.autosave);
				this.controller.SaveState(Controller.STATE_EDIT);
			}

			private UpdateDataAndSave(): void {
				this.UpdateData(
					this.$header.val().toString(),
					this.GetDiscount(),
					true
				);
				this.Save();
			}

			private Save(): void {
				Site.Common.DB.Connect().then((db: IDBDatabase) => {
					let data = {
						id: this.id,
						eid: this.eid,
						datecr: this.datecr,
						datemd: this.datemd,

						header: this.header,
						discount: this.discount
					};
					Site.Common.DB.Put(db, 'estimate_table', data);
					this.controller.SaveState(Controller.STATE_SAVE);
				});
			}

			private GetDiscount(): number {
				let discount = parseFloat(this.$discount.val().toString());
				if (isNaN(discount)) discount = 0;

				return discount;
			}

			private Input(): void {
				this.discount = this.GetDiscount();
				this.Sum();
			}

			private EnterPercent(): void {
				this.$discount.val(this.GetDiscount());
			}

			private Visible(): void {
				this.visible = !this.visible;

				if (this.visible) {
					this.$visible.removeClass('show').attr('title', 'Скрыть таблицу');
					this.$wrap.removeClass('hide');
				} else {
					this.$visible.addClass('show').attr('title', 'Показать таблицу');
					this.$wrap.addClass('hide');
				}
			}

			private Remove(): void {
				Site.Common.DB.Connect().then((db: IDBDatabase) => {
					Site.Common.DB.Delete(db, 'estimate_table', this.id);
				});

				this.estimate.RemoveTable(this.id);
				this.$list.remove();
			}

		}

		type TypeRecordData = { id: number, tid: number, datecr: string, datemd : string, name: string, count: number, unit: string, price: number };

		class Record {
			/* Variables */
			private id								: number;
			private tid								: number;
			private datecr							: string;
			private datemd							: string;

			private name							: string;
			private count							: number;
			private unit							: string;
			private price							: number;

			private sum								: number;

			private readonly controller				: Controller;
			private readonly table					: Table;
			private readonly autosave				: number;
			private timer							?: number;

			/* Elements */
			private readonly $before				: JQuery;
			private readonly $tr					: JQuery;
			private readonly $remove				: JQuery;
			private readonly $name					: JQuery;
			private readonly $count					: JQuery;
			private readonly $unit					: JQuery;
			private readonly $price					: JQuery;
			private readonly $sum					: JQuery;

			constructor(id: number, tid: number, data: TypeRecordData | null, $before: JQuery, controller: Controller, table: Table) {
				/* Set variables */
				this.id								= id;
				this.tid							= tid;

				this.sum							= 0;

				this.controller						= controller;
				this.table							= table;
				this.timer							= null;
				this.autosave						= 2000;

				/* Set elements */
				this.$before						= $before;
				this.$tr							= $('<tr/>', {class: 'line'})
				this.$remove						= $('<span/>', {class: 'item del negative', title: 'Удалить строку'});
				this.$name							= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$count							= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$unit							= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$price							= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$sum							= $('<span/>');

				/* Events */
				this.$remove.on('click', this.Remove.bind(this));

				/* Building DOM */
				this.$tr.append(
					$('<td/>', {class: 'number glob_tabu'}).append(this.$remove),
					$('<td/>').append(this.$name, $('<span/>', {class: 'glob_print'})),
					$('<td/>', {class: 'number'}).append(this.$count),
					$('<td/>', {class: 'number'}).append(this.$unit),
					$('<td/>', {class: 'number'}).append(this.$price),
					$('<td/>', {class: 'number'}).append(this.$sum)
				);

				/* Duplicate */
				DuplicateInit(this.$name);
				DuplicateInit(this.$count, 'blur');
				DuplicateInit(this.$unit);
				DuplicateInit(this.$price, 'blur');

				this.$before.before(this.$tr);

				if (!this.id) {
					this.CreateData(Number(localStorage.getItem('EstimateRecordIter')) || 1, '', 0, '', 0, true, true);
					localStorage.setItem('EstimateRecordIter', (this.id + 1).toString());

					this.Save();
				} else {
					this.CreateData(data.id, data.name, data.count, data.unit, data.price, data.datecr, data.datemd);
				}

				this.Fill();
				this.AutosaveEnable();
				this.Sum();
				this.$sum.text(this.sum);
				this.$count.on('blur', this.EnterCount.bind(this));
				this.$price.on('blur', this.EnterPrice.bind(this));
				this.$count.on('input', this.Input.bind(this));
				this.$price.on('input', this.Input.bind(this));
				this.$count.on('focus', EmptyIfZero);
				this.$price.on('focus', EmptyIfZero);
			}

			public GetId(): number {
				return this.id;
			}

			public GetSum(): number {
				return this.sum;
			}

			private Fill(): void {
				this.$name.val(this.name).trigger('input');
				this.$count.val(this.count).trigger('blur');
				this.$unit.val(this.unit).trigger('input');
				this.$price.val(this.price).trigger('blur');
			}

			private AutosaveEnable(): void {
				this.$name.on('input', this.Commit.bind(this));
				this.$count.on('input', this.Commit.bind(this));
				this.$unit.on('input', this.Commit.bind(this));
				this.$price.on('input', this.Commit.bind(this));
			}

			private CreateData(id: number, name: string, count: number, unit: string, price: number, datecr: string | boolean = false, datemd: string | boolean = false): void {
				this.id = id;
				if (datecr) this.datecr = (datecr === true) ? GetDate() : datecr;

				this.UpdateData(name, count, unit, price, datemd);
			}

			private UpdateData(name: string, count: number, unit: string, price: number, datemd: string | boolean = false): void {
				if (datemd) this.datemd = (datemd === true) ? GetDate() : datemd;

				this.name = name;
				this.count = count;
				this.unit = unit;
				this.price = price;
			}

			private Commit(): void {
				clearTimeout(this.timer);
				this.timer = setTimeout(this.UpdateDataAndSave.bind(this), this.autosave);
				this.controller.SaveState(Controller.STATE_EDIT);
			}

			private UpdateDataAndSave(): void {
				let count = parseFloat(this.$count.val().toString());
				if (isNaN(count)) count = 0;

				let price = parseFloat(this.$price.val().toString());
				if (isNaN(price)) price = 0;

				this.UpdateData(
					this.$name.val().toString(),
					count,
					this.$unit.val().toString(),
					price,
					true
				);
				this.Save();
			}

			private Save(): void {
				Site.Common.DB.Connect().then((db: IDBDatabase) => {
					let data = {
						id: this.id,
						tid: this.tid,
						datecr: this.datecr,
						datemd: this.datemd,

						name: this.name,
						count: this.count,
						unit: this.unit,
						price: this.price
					};
					Site.Common.DB.Put(db, 'estimate_record', data);
					this.controller.SaveState(Controller.STATE_SAVE);
				});
			}

			private GetCount(): number {
				let count = parseFloat(this.$count.val().toString());
				if (isNaN(count)) count = 0;

				return count;
			}

			private EnterCount(): void {
				this.$count.val(this.GetCount());
			}

			private GetPrice(): number {
				let price = +parseFloat(this.$price.val().toString()).toFixed(2);
				if (isNaN(price)) price = 0;

				return price;
			}

			private EnterPrice(): void {
				this.$price.val(this.GetPrice());
			}

			private Input(): void {
				this.Sum();
				this.$sum.text(this.sum);
				this.table.Sum();
			}

			private Sum(): void {
				this.sum = +((this.GetPrice() * this.GetCount()).toFixed(2));
			}

			private Remove(): void {
				Site.Common.DB.Connect().then((db: IDBDatabase) => {
					Site.Common.DB.Delete(db, 'estimate_record', this.id);
				});

				this.table.RemoveRecord(this.id);
				this.$tr.remove();
			}

		}

	}
}