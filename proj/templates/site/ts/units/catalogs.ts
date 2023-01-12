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

		type TypeStateEdit = 1;
		type TypeStateSave = 2;
		type TypeStateAutoSave = TypeStateEdit | TypeStateSave;
		type TypeActTableData = { id: number, did: number, datecr: string, datemd : string, header: string, discount: number };
		type TypePriceListTableData = { id: number, did: number, datecr: string, datemd : string, header: string };
		type TypeActRecordData = { id: number, tid: number, datecr: string, datemd : string, name: string, count: number, unit: string, price: number };
		type TypePriceListRecordData = { id: number, tid: number, datecr: string, datemd : string, name: string, price: string };

		class ActController {
			/* Variables */
			static readonly STATE_EDIT				: TypeStateEdit = 1;
			static readonly STATE_SAVE				: TypeStateSave = 2;
			protected states_sources				: { document: TypeStateAutoSave, table: TypeStateAutoSave, record: TypeStateAutoSave };
			protected documentId					: number | null;
			protected document						: ActDocument;
			protected tables_names					: { [key: string]: string };
			protected iters_names					: { [key: string]: string };
			protected texts							: { [key: string]: string };

			/* Elements */
			protected $view							: JQuery;
			protected $control						: JQuery;
			protected $btns							: JQuery;
			protected $info							: JQuery;
			protected $state						: JQuery;
			protected $btn_new						: JQuery;
			protected $select						: JQuery;
			protected $container					: JQuery;

			constructor(selector: string, tables_names: {[key: string]: string}, iters_names: {[key: string]: string}, texts: {[key: string]: string}) {
				/* Variables */
				this.documentId						= null;
				this.tables_names					= tables_names;
				this.iters_names					= iters_names;
				this.texts							= texts;

				/* Set elements */
				this.$view 							= $(selector);
				this.$control 						= $('<div/>', {class: 'control glob_print_tabu'});
				this.$btns 							= $('<div/>', {class: 'btns'});
				this.$btn_new 						= $('<input/>', {type: 'button', class: 'img new', value: this.texts['new']});
				this.$select 						= $('<select/>');
				this.$info 							= $('<div/>', {class: 'info'});
				this.$state 						= $('<span/>', {class: 'state'});
				this.$container 					= $('<div/>', {class: 'container'});

				/* Building DOM */
				this.$view.append(
					this.$control.append(
						this.$btns.append(
							this.$btn_new,
							this.$select.append(
								$('<option/>', {value: '', selected: true, disabled: true, hidden: true}).text(this.texts['select'])
							)
						),
						this.$info.append(
							this.$state
						)
					),
					this.$container
				);

				Site.Common.DB.Connect().then((result: IDBDatabase) => {
					Site.Common.DB.Cursor(result, this.tables_names['document'], cursor => {
						let key = cursor.key;
						let value = cursor.value;

						this.AddOption(key, value.datecr, value.name);
					}, () => {
						new Skins.Select(this.$select, this.OnDeleteDocument, {self: this});
					});
				});

				/* Events */
				this.$btn_new.on('click', this.OnCreateDocument.bind(this));
				this.$select.on('change', this.LoadDocument.bind(this));
			}

			public GetTableName(alias: string): string {
				return this.tables_names[alias];
			}

			public GetIterName(alias: string): string {
				return this.iters_names[alias];
			}

			public GetTextName(alias: string): string {
				return this.texts[alias];
			}

			protected AddOption(id: number, datecr: string, name: string): void {
				this.$select.append(
					$('<option/>', {value: id}).text(`«${name}» от ${datecr}`)
				);
			}

			protected OnCreateDocument(): void {
				let $input = $('<input/>', {type: 'text', placeholder: 'Название'});
				Site.Common.Window.Interactive($input, null, [['yes', 'Создать', false]], () => this.CreateDocument($input.closest('.instance').children('.space'), $input.val().toString().trim()));
			}

			protected CreateDocument($space: JQuery, name: string): void {
				if (name === '') return;
				this.$container.empty();
				this.states_sources = {
					document: ActController.STATE_SAVE,
					table: ActController.STATE_SAVE,
					record: ActController.STATE_SAVE
				};

				this.document = new ActDocument(0, name, this.$container, this);
				let data = this.document.GetDate();
				this.documentId = data.id;
				$space.trigger('click');
				this.AddOption(data.id, data.datecr, data.name);
			}

			private LoadDocument() {
				this.$container.empty();
				this.states_sources = {
					document: ActController.STATE_SAVE,
					table: ActController.STATE_SAVE,
					record: ActController.STATE_SAVE
				};

				this.document = new ActDocument(Number(this.$select.val()), '', this.$container, this);

				let data = this.document.GetDate();
				this.documentId = data.id;
			}

			private OnDeleteDocument(id: number, data: any) {
				Site.Common.Window.Interactive(Site.Common.GetMessageBlock(data.self.texts['delete']), null, [['yes', 'Да'], ['no', 'Нет']], () => data.self.DeleteDocument(id));
			}

			private DeleteDocument(id: number) {
				Site.Common.DB.Connect().then((db: IDBDatabase) => {
					Site.Common.DB.CursorIndex(db, this.tables_names['table'], 'did', IDBKeyRange.only(id), cursor => {
						Site.Common.DB.CursorIndex(db, this.tables_names['record'], 'tid', IDBKeyRange.only(cursor.value.id), cursor => {
							Site.Common.DB.Delete(db, this.tables_names['record'], cursor.value.id);
						});
						Site.Common.DB.Delete(db, this.tables_names['table'], cursor.value.id);
					});
					Site.Common.DB.Delete(db, this.tables_names['document'], id);
				});

				this.$select.children(`option[value="${id}"]`).remove();
				if (id === this.documentId) this.$container.empty();
			}

			public SaveState(state: TypeStateAutoSave, source: 'document' | 'table' | 'record') {
				let old_sum = 0;
				for (let i in this.states_sources) if (this.states_sources[i] === ActController.STATE_EDIT) old_sum++;

				this.states_sources[source] = state;

				let new_sum = 0;
				for (let i in this.states_sources) if (this.states_sources[i] === ActController.STATE_EDIT) new_sum++;

				let _class = '';
				let _text = '';
				switch (state) {
					case ActController.STATE_EDIT: if (!old_sum) { _class = 'edit'; _text = 'Изменено'; } break;
					case ActController.STATE_SAVE: if (old_sum && !new_sum) { _class = 'save'; _text = 'Сохранено'; } break;
				}
				if (_class) this.$state.removeClass().addClass(_class).text(_text);
			}

		}

		export class EstimateController extends ActController {

			constructor(selector: string) {
				let tables = {
					document: 'estimate',
					table: 'estimate_table',
					record: 'estimate_record'
				};
				let iters = {
					document: 'EstimateIter',
					table: 'EstimateTableIter',
					record: 'EstimateRecordIter'
				};
				let texts = {
					name: 'Смета',
					new: 'Новая',
					select: 'Выберите смету',
					delete: 'Удалить смету?'
				};

				super(selector, tables, iters, texts);
			}

		}

		export class CertificateController extends ActController {

			constructor(selector: string) {
				let tables = {
					document: 'certificate',
					table: 'certificate_table',
					record: 'certificate_record'
				};
				let iters = {
					document: 'CertificateIter',
					table: 'CertificateTableIter',
					record: 'CertificateRecordIter'
				};
				let texts = {
					name: 'Акт выполненых работ',
					new: 'Новый',
					select: 'Выберите акт',
					delete: 'Удалить акт?'
				};

				super(selector, tables, iters, texts);
			}

		}

		class ActDocument {
			/* Variables */
			private id								: number;
			private datecr							: string;
			private datemd							: string;

			private name							: string;
			private company							: string;
			private address							: string;
			private phone							: string;
			private mail							: string;
			private date							: string;

			private readonly controller				: ActController;
			private readonly tables					: {[key: number]: ActTable};
			private readonly autosave				: number;
			private timer							?: number;

			/* Elements */
			private readonly $container				: JQuery;
			private readonly $btns					: JQuery;
			private readonly $btn_add				: JQuery;
			private readonly $btn_print				: JQuery;
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

			constructor(id: number, name, $container: JQuery, controller: ActController) {
				/* Set variables */
				this.id								= id;

				this.controller						= controller;
				this.tables 						= {};
				this.timer							= null;
				this.autosave						= 2000;

				/* Set elements */
				this.$container 					= $container;

				this.$btns 							= $('<div/>', {class: 'btns glob_print_tabu'});
				this.$btn_add 						= $('<input/>', {type: 'button', value: 'Добавить таблицу', class: 'img add_table'});
				this.$btn_print 					= $('<input/>', {type: 'button', value: 'Печать', class: 'img print'});
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

				/* Events */
				this.$btn_add.on('click', () => this.AddTable(0));
				this.$btn_print.on('click', () => window.print());

				/* Building DOM */
				this.$wrap.append(
					this.$btns.append(
						this.$btn_add,
						this.$btn_print
					),
					this.$header.append(
						this.$caption.text(this.controller.GetTextName('name')),
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
					let iter_name = this.controller.GetIterName('document');
					this.CreateData(Number(localStorage.getItem(iter_name)) || 1, name, '', '', '', '', Site.Common.UIDate.Today(), true, true);
					localStorage.setItem(iter_name, (this.id + 1).toString());

					this.Save();
					this.Fill();
					this.AutosaveEnable();
				} else {
					Site.Common.DB.Connect().then((db: IDBDatabase) => {
						Site.Common.DB.Get(db, this.controller.GetTableName('document'), this.id).then((result) => {
							this.CreateData(result.id, result.name, result.company, result.address, result.mail, result.phone, result.date, result.datecr, result.datemd);
							this.Fill();
							this.AutosaveEnable();
						});
						Site.Common.DB.CursorIndex(db, this.controller.GetTableName('table'), 'did', IDBKeyRange.only(this.id), cursor => {
							this.AddTable(cursor.primaryKey, cursor.value);
						});
					});
				}
			}

			public GetDate(): {id: number, datecr: string, name: string} {
				return {
					id: this.id,
					datecr: this.datecr,

					name: this.name
				};
			}

			public AddTable(id: number, data: TypeActTableData | null = null): void {
				this.tables[id] = new ActTable(id, this.id, data, this.$lists, this.controller, this);
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

			private CreateData(id: number, name: string, company: string, address: string, mail: string, phone: string, date: string, datecr: string | boolean = false, datemd: string | boolean = false): void {
				this.id = id;
				this.name = name;
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
				this.controller.SaveState(ActController.STATE_EDIT, 'document');
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
						name: this.name,
						datecr: this.datecr,
						datemd: this.datemd,

						company: this.company,
						address: this.address,
						mail: this.mail,
						phone: this.phone,
						date: this.date
					};
					Site.Common.DB.Put(db, this.controller.GetTableName('document'), data);
					this.controller.SaveState(ActController.STATE_SAVE, 'document');
				});
			}

		}

		class ActTable {
			/* Variables */
			private id								: number;
			private readonly did					: number;
			private datecr							: string;
			private datemd							: string;

			private header							: string;
			private discount						: number;

			private sum								: number;

			private readonly controller				: ActController;
			private readonly document				: ActDocument;
			private readonly records				: {[key: number]: ActRecord};
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

			constructor(id: number, did: number, data: TypeActTableData | null, $container: JQuery, controller: ActController, document: ActDocument) {
				/* Set variables */
				this.id								= id;
				this.did							= did;

				this.sum							= 0;

				this.controller						= controller;
				this.document						= document;
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
				this.$remove.on('click', this.QuestionRemove.bind(this));
				this.$add_line.on('click', () => this.AddRecord(0));
				this.$collapse.on('click', this.CollapseRecords.bind(this));

				/* Building DOM */
				this.$list.append(
					$('<div/>', {class: 'control glob_print_tabu'}).append(
						this.$visible,
						this.$remove
					),
					this.$wrap.append(
						$('<div/>', {class: 'title'}).append(this.$header),
						this.$table.append(
							$('<thead/>').append(
								$('<tr/>').append(
									$('<th/>', {class: 'glob_print_tabu'}).append($('<span/>').text('+/-')),
									$('<th/>').text('Наименование'),
									$('<th/>').text('Количество'),
									$('<th/>').text('Единица измерения'),
									$('<th/>').text('Цена'),
									$('<th/>').text('Сумма')
								)
							),
							$('<tbody/>').append(
								this.$tr_sum.append(
									$('<td/>', {class: 'number glob_print_tabu'}).append(this.$add_line),
									$('<td/>', {colspan: 3}),
									$('<td/>').text('Всего'),
									$('<td/>', {class: 'number'}).append(this.$sum),
								),
								$('<tr/>').append(
									$('<td/>', {class: 'number glob_print_tabu'}).append(
										this.$collapse
									),
									$('<td/>', {colspan: 3}),
									$('<td/>').text('Скидка, %'),
									$('<td/>', {class: 'number'}).append(this.$discount),
								),
								$('<tr/>', {class: 'total'}).append(
									$('<td/>', {class: 'glob_print_tabu'}),
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
					let iter_name = this.controller.GetIterName('table');
					this.CreateData(Number(localStorage.getItem(iter_name)) || 1, '', 0, true, true);
					localStorage.setItem(iter_name, (this.id + 1).toString());

					this.Save();
				} else {
					this.CreateData(data.id, data.header, data.discount, data.datecr, data.datemd);

					Site.Common.DB.Connect().then((db: IDBDatabase) => {
						Site.Common.DB.CursorIndex(db, this.controller.GetTableName('record'), 'tid', IDBKeyRange.only(this.id), cursor => {
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

			private AddRecord(id: number, data: TypeActRecordData | null = null): void {
				let _record = new ActRecord(id, this.id, data, this.$tr_sum, this.controller, this);
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
				this.controller.SaveState(ActController.STATE_EDIT, 'table');
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
						did: this.did,
						datecr: this.datecr,
						datemd: this.datemd,

						header: this.header,
						discount: this.discount
					};
					Site.Common.DB.Put(db, this.controller.GetTableName('table'), data);
					this.controller.SaveState(ActController.STATE_SAVE, 'table');
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

			private QuestionRemove() {
				Site.Common.Window.Interactive(Site.Common.GetMessageBlock('Удалить таблицу?'), null, [['yes', 'Да'], ['no', 'Нет']], this.Remove.bind(this));
			}

			private Remove(): void {
				Site.Common.DB.Connect().then((db: IDBDatabase) => {
					Site.Common.DB.CursorIndex(db, this.controller.GetTableName('record'), 'tid', IDBKeyRange.only(this.id), cursor => {
						Site.Common.DB.Delete(db, this.controller.GetTableName('record'), cursor.value.id);
					});
					Site.Common.DB.Delete(db, this.controller.GetTableName('table'), this.id);
				});

				this.document.RemoveTable(this.id);
				this.$list.remove();
			}

		}

		class ActRecord {
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

			private readonly controller				: ActController;
			private readonly table					: ActTable;
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

			constructor(id: number, tid: number, data: TypeActRecordData | null, $before: JQuery, controller: ActController, table: ActTable) {
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
				this.$remove.on('click', this.QuestionRemove.bind(this));

				/* Building DOM */
				this.$tr.append(
					$('<td/>', {class: 'number glob_print_tabu'}).append(this.$remove),
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
					let iter_name = this.controller.GetIterName('record');
					this.CreateData(Number(localStorage.getItem(iter_name)) || 1, '', 0, '', 0, true, true);
					localStorage.setItem(iter_name, (this.id + 1).toString());

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
				this.controller.SaveState(ActController.STATE_EDIT, 'record');
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
					Site.Common.DB.Put(db, this.controller.GetTableName('record'), data);
					this.controller.SaveState(ActController.STATE_SAVE, 'record');
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

			private QuestionRemove() {
				Site.Common.Window.Interactive(Site.Common.GetMessageBlock('Удалить запись?'), null, [['yes', 'Да'], ['no', 'Нет']], this.Remove.bind(this));
			}

			private Remove(): void {
				Site.Common.DB.Connect().then((db: IDBDatabase) => {
					Site.Common.DB.Delete(db, this.controller.GetTableName('record'), this.id);
				});

				this.table.RemoveRecord(this.id);
				this.$tr.remove();
			}

		}

		export class PriceListController {
			/* Variables */
			static readonly STATE_EDIT				: TypeStateEdit = 1;
			static readonly STATE_SAVE				: TypeStateSave = 2;
			protected states_sources				: { document: TypeStateAutoSave, table: TypeStateAutoSave, record: TypeStateAutoSave };
			protected documentId					: number | null;
			protected document						: PriceListDocument;
			protected tables_names					: { [key: string]: string };
			protected iters_names					: { [key: string]: string };
			protected texts							: { [key: string]: string };

			/* Elements */
			protected $view							: JQuery;
			protected $control						: JQuery;
			protected $btns							: JQuery;
			protected $info							: JQuery;
			protected $state						: JQuery;
			protected $btn_new						: JQuery;
			protected $select						: JQuery;
			protected $container					: JQuery;

			constructor(selector: string) {
				/* Variables */
				this.documentId						= null;
				this.tables_names					= {
					document: 'price_list',
					table: 'price_list_table',
					record: 'price_list_record'
				};
				this.iters_names					= {
					document: 'PriceListIter',
					table: 'PriceListTableIter',
					record: 'PriceListRecordIter'
				};
				this.texts							= {
					name: 'Прайс-лист',
					new: 'Новый',
					select: 'Выберите прайс-лист',
					delete: 'Удалить прайс-лист?'
				};

				/* Set elements */
				this.$view 							= $(selector);
				this.$control 						= $('<div/>', {class: 'control glob_print_tabu'});
				this.$btns 							= $('<div/>', {class: 'btns'});
				this.$btn_new 						= $('<input/>', {type: 'button', class: 'img new', value: this.texts['new']});
				this.$select 						= $('<select/>');
				this.$info 							= $('<div/>', {class: 'info'});
				this.$state 						= $('<span/>', {class: 'state'});
				this.$container 					= $('<div/>', {class: 'container'});

				/* Building DOM */
				this.$view.append(
					this.$control.append(
						this.$btns.append(
							this.$btn_new,
							this.$select.append(
								$('<option/>', {value: '', selected: true, disabled: true, hidden: true}).text(this.texts['select'])
							)
						),
						this.$info.append(
							this.$state
						)
					),
					this.$container
				);

				Site.Common.DB.Connect().then((result: IDBDatabase) => {
					Site.Common.DB.Cursor(result, this.tables_names['document'], cursor => {
						let key = cursor.key;
						let value = cursor.value;

						this.AddOption(key, value.datecr, value.name);
					}, () => {
						new Skins.Select(this.$select, this.OnDeleteDocument, {self: this});
					});
				});

				/* Events */
				this.$btn_new.on('click', this.OnCreateDocument.bind(this));
				this.$select.on('change', this.LoadDocument.bind(this));
			}

			public GetTableName(alias: string): string {
				return this.tables_names[alias];
			}

			public GetIterName(alias: string): string {
				return this.iters_names[alias];
			}

			public GetTextName(alias: string): string {
				return this.texts[alias];
			}

			protected AddOption(id: number, datecr: string, name: string): void {
				this.$select.append(
					$('<option/>', {value: id}).text(`«${name}» от ${datecr}`)
				);
			}

			protected OnCreateDocument(): void {
				let $input = $('<input/>', {type: 'text', placeholder: 'Название'});
				Site.Common.Window.Interactive($input, null, [['yes', 'Создать', false]], () => this.CreateDocument($input.closest('.instance').children('.space'), $input.val().toString().trim()));
			}

			protected CreateDocument($space: JQuery, name: string): void {
				if (name === '') return;
				this.$container.empty();
				this.states_sources = {
					document: PriceListController.STATE_SAVE,
					table: PriceListController.STATE_SAVE,
					record: PriceListController.STATE_SAVE
				};

				this.document = new PriceListDocument(0, name, this.$container, this);
				let data = this.document.GetDate();
				this.documentId = data.id;
				$space.trigger('click');
				this.AddOption(data.id, data.datecr, data.name);
			}

			private LoadDocument() {
				this.$container.empty();
				this.states_sources = {
					document: PriceListController.STATE_SAVE,
					table: PriceListController.STATE_SAVE,
					record: PriceListController.STATE_SAVE
				};

				this.document = new PriceListDocument(Number(this.$select.val()), '', this.$container, this);

				let data = this.document.GetDate();
				this.documentId = data.id;
			}

			private OnDeleteDocument(id: number, data: any) {
				Site.Common.Window.Interactive(Site.Common.GetMessageBlock(data.self.texts['delete']), null, [['yes', 'Да'], ['no', 'Нет']], () => data.self.DeleteDocument(id));
			}

			private DeleteDocument(id: number) {
				Site.Common.DB.Connect().then((db: IDBDatabase) => {
					Site.Common.DB.CursorIndex(db, this.tables_names['table'], 'did', IDBKeyRange.only(id), cursor => {
						Site.Common.DB.CursorIndex(db, this.tables_names['record'], 'tid', IDBKeyRange.only(cursor.value.id), cursor => {
							Site.Common.DB.Delete(db, this.tables_names['record'], cursor.value.id);
						});
						Site.Common.DB.Delete(db, this.tables_names['table'], cursor.value.id);
					});
					Site.Common.DB.Delete(db, this.tables_names['document'], id);
				});

				this.$select.children(`option[value="${id}"]`).remove();
				if (id === this.documentId) this.$container.empty();
			}

			public SaveState(state: TypeStateAutoSave, source: 'document' | 'table' | 'record') {
				let old_sum = 0;
				for (let i in this.states_sources) if (this.states_sources[i] === PriceListController.STATE_EDIT) old_sum++;

				this.states_sources[source] = state;

				let new_sum = 0;
				for (let i in this.states_sources) if (this.states_sources[i] === PriceListController.STATE_EDIT) new_sum++;

				let _class = '';
				let _text = '';
				switch (state) {
					case PriceListController.STATE_EDIT: if (!old_sum) { _class = 'edit'; _text = 'Изменено'; } break;
					case PriceListController.STATE_SAVE: if (old_sum && !new_sum) { _class = 'save'; _text = 'Сохранено'; } break;
				}
				if (_class) this.$state.removeClass().addClass(_class).text(_text);
			}

		}

		class PriceListDocument {
			/* Variables */
			private id								: number;
			private datecr							: string;
			private datemd							: string;

			private name							: string;
			private company							: string;
			private address							: string;
			private phone							: string;
			private mail							: string;
			private date							: string;

			private readonly controller				: PriceListController;
			private readonly tables					: {[key: number]: PriceListTable};
			private readonly autosave				: number;
			private timer							?: number;

			/* Elements */
			private readonly $container				: JQuery;
			private readonly $btns					: JQuery;
			private readonly $btn_add				: JQuery;
			private readonly $btn_print				: JQuery;
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

			constructor(id: number, name, $container: JQuery, controller: PriceListController) {
				/* Set variables */
				this.id								= id;

				this.controller						= controller;
				this.tables 						= {};
				this.timer							= null;
				this.autosave						= 2000;

				/* Set elements */
				this.$container 					= $container;

				this.$btns 							= $('<div/>', {class: 'btns glob_print_tabu'});
				this.$btn_add 						= $('<input/>', {type: 'button', value: 'Добавить таблицу', class: 'img add_table'});
				this.$btn_print 					= $('<input/>', {type: 'button', value: 'Печать', class: 'img print'});
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

				/* Events */
				this.$btn_add.on('click', () => this.AddTable(0));
				this.$btn_print.on('click', () => window.print());

				/* Building DOM */
				this.$wrap.append(
					this.$btns.append(
						this.$btn_add,
						this.$btn_print
					),
					this.$header.append(
						this.$caption.text(this.controller.GetTextName('name')),
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
					let iter_name = this.controller.GetIterName('document');
					this.CreateData(Number(localStorage.getItem(iter_name)) || 1, name, '', '', '', '', Site.Common.UIDate.Today(), true, true);
					localStorage.setItem(iter_name, (this.id + 1).toString());

					this.Save();
					this.Fill();
					this.AutosaveEnable();
				} else {
					Site.Common.DB.Connect().then((db: IDBDatabase) => {
						Site.Common.DB.Get(db, this.controller.GetTableName('document'), this.id).then((result) => {
							this.CreateData(result.id, result.name, result.company, result.address, result.mail, result.phone, result.date, result.datecr, result.datemd);
							this.Fill();
							this.AutosaveEnable();
						});
						Site.Common.DB.CursorIndex(db, this.controller.GetTableName('table'), 'did', IDBKeyRange.only(this.id), cursor => {
							this.AddTable(cursor.primaryKey, cursor.value);
						});
					});
				}
			}

			public GetDate(): {id: number, datecr: string, name: string} {
				return {
					id: this.id,
					datecr: this.datecr,

					name: this.name
				};
			}

			public AddTable(id: number, data: TypePriceListTableData | null = null): void {
				this.tables[id] = new PriceListTable(id, this.id, data, this.$lists, this.controller, this);
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

			private CreateData(id: number, name: string, company: string, address: string, mail: string, phone: string, date: string, datecr: string | boolean = false, datemd: string | boolean = false): void {
				this.id = id;
				this.name = name;
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
				this.controller.SaveState(PriceListController.STATE_EDIT, 'document');
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
						name: this.name,
						datecr: this.datecr,
						datemd: this.datemd,

						company: this.company,
						address: this.address,
						mail: this.mail,
						phone: this.phone,
						date: this.date
					};
					Site.Common.DB.Put(db, this.controller.GetTableName('document'), data);
					this.controller.SaveState(PriceListController.STATE_SAVE, 'document');
				});
			}

		}

		class PriceListTable {
			/* Variables */
			private id								: number;
			private readonly did					: number;
			private datecr							: string;
			private datemd							: string;

			private header							: string;

			private sum								: number;

			private readonly controller				: PriceListController;
			private readonly document				: PriceListDocument;
			private readonly records				: {[key: number]: PriceListRecord};
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

			constructor(id: number, did: number, data: TypePriceListTableData | null, $container: JQuery, controller: PriceListController, document: PriceListDocument) {
				/* Set variables */
				this.id								= id;
				this.did							= did;

				this.sum							= 0;

				this.controller						= controller;
				this.document						= document;
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
				this.$tr_sum 						= $('<tr/>', {class: 'glob_print_tabu'});

				/* Events */
				this.$visible.on('click', this.Visible.bind(this));
				this.$remove.on('click', this.QuestionRemove.bind(this));
				this.$add_line.on('click', () => this.AddRecord(0));
				this.$collapse.on('click', this.CollapseRecords.bind(this));

				/* Building DOM */
				this.$list.append(
					$('<div/>', {class: 'control glob_print_tabu'}).append(
						this.$visible,
						this.$remove
					),
					this.$wrap.append(
						$('<div/>', {class: 'title'}).append(this.$header),
						this.$table.append(
							$('<thead/>').append(
								$('<tr/>').append(
									$('<th/>', {class: 'glob_print_tabu'}).append($('<span/>').text('+/-')),
									$('<th/>').text('Наименование'),
									$('<th/>').text('Цена')
								)
							),
							$('<tbody/>').append(
								this.$tr_sum.append(
									$('<td/>', {class: 'number items_margin_bottom_cut'}).append(
										$('<div/>').append(this.$add_line),
										$('<div/>').append(this.$collapse)
									),
									$('<td/>', {colspan: 2})
								),
							)
						)
					)
				);

				/* Duplicate */
				DuplicateInit(this.$header);

				this.$container.append(this.$list);

				if (!this.id) {
					let iter_name = this.controller.GetIterName('table');
					this.CreateData(Number(localStorage.getItem(iter_name)) || 1, '', true, true);
					localStorage.setItem(iter_name, (this.id + 1).toString());

					this.Save();
				} else {
					this.CreateData(data.id, data.header, data.datecr, data.datemd);

					Site.Common.DB.Connect().then((db: IDBDatabase) => {
						Site.Common.DB.CursorIndex(db, this.controller.GetTableName('record'), 'tid', IDBKeyRange.only(this.id), cursor => {
							this.AddRecord(cursor.primaryKey, cursor.value);
						});
					});
				}

				this.Fill();
				this.AutosaveEnable();
			}

			private AddRecord(id: number, data: TypePriceListRecordData | null = null): void {
				let _record = new PriceListRecord(id, this.id, data, this.$tr_sum, this.controller, this);
				let _id = _record.GetId();
				this.records[_id] = _record;
			}

			public RemoveRecord(id: number): void {
				delete this.records[id];
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
			}

			private AutosaveEnable(): void {
				this.$header.on('input', this.Commit.bind(this));
			}

			private CreateData(id: number, header: string, datecr: string | boolean = false, datemd: string | boolean = false): void {
				this.id = id;
				if (datecr) this.datecr = (datecr === true) ? GetDate() : datecr;

				this.UpdateData(header, datemd);
			}

			private UpdateData(header: string, datemd: string | boolean = false): void {
				if (datemd) this.datemd = (datemd === true) ? GetDate() : datemd;

				this.header = header;
			}

			private Commit(): void {
				clearTimeout(this.timer);
				this.timer = setTimeout(this.UpdateDataAndSave.bind(this), this.autosave);
				this.controller.SaveState(PriceListController.STATE_EDIT, 'table');
			}

			private UpdateDataAndSave(): void {
				this.UpdateData(
					this.$header.val().toString(),
					true
				);
				this.Save();
			}

			private Save(): void {
				Site.Common.DB.Connect().then((db: IDBDatabase) => {
					let data = {
						id: this.id,
						did: this.did,
						datecr: this.datecr,
						datemd: this.datemd,

						header: this.header
					};
					Site.Common.DB.Put(db, this.controller.GetTableName('table'), data);
					this.controller.SaveState(PriceListController.STATE_SAVE, 'table');
				});
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

			private QuestionRemove() {
				Site.Common.Window.Interactive(Site.Common.GetMessageBlock('Удалить таблицу?'), null, [['yes', 'Да'], ['no', 'Нет']], this.Remove.bind(this));
			}

			private Remove(): void {
				Site.Common.DB.Connect().then((db: IDBDatabase) => {
					Site.Common.DB.CursorIndex(db, this.controller.GetTableName('record'), 'tid', IDBKeyRange.only(this.id), cursor => {
						Site.Common.DB.Delete(db, this.controller.GetTableName('record'), cursor.value.id);
					});
					Site.Common.DB.Delete(db, this.controller.GetTableName('table'), this.id);
				});

				this.document.RemoveTable(this.id);
				this.$list.remove();
			}

		}

		class PriceListRecord {
			/* Variables */
			private id								: number;
			private tid								: number;
			private datecr							: string;
			private datemd							: string;

			private name							: string;
			private price							: string;

			private readonly controller				: PriceListController;
			private readonly table					: PriceListTable;
			private readonly autosave				: number;
			private timer							?: number;

			/* Elements */
			private readonly $before				: JQuery;
			private readonly $tr					: JQuery;
			private readonly $remove				: JQuery;
			private readonly $name					: JQuery;
			private readonly $price					: JQuery;

			constructor(id: number, tid: number, data: TypePriceListRecordData | null, $before: JQuery, controller: PriceListController, table: PriceListTable) {
				/* Set variables */
				this.id								= id;
				this.tid							= tid;

				this.controller						= controller;
				this.table							= table;
				this.timer							= null;
				this.autosave						= 2000;

				/* Set elements */
				this.$before						= $before;
				this.$tr							= $('<tr/>', {class: 'line'})
				this.$remove						= $('<span/>', {class: 'item del negative', title: 'Удалить строку'});
				this.$name							= $('<input/>', {type: 'text', placeholder: '...🖊'});
				this.$price							= $('<input/>', {type: 'text', placeholder: '...🖊'});

				/* Events */
				this.$remove.on('click', this.QuestionRemove.bind(this));

				/* Building DOM */
				this.$tr.append(
					$('<td/>', {class: 'number glob_print_tabu'}).append(this.$remove),
					$('<td/>').append(this.$name, $('<span/>', {class: 'glob_print'})),
					$('<td/>', {class: 'number'}).append(this.$price),
				);

				/* Duplicate */
				DuplicateInit(this.$name);
				DuplicateInit(this.$price);

				this.$before.before(this.$tr);

				if (!this.id) {
					let iter_name = this.controller.GetIterName('record');
					this.CreateData(Number(localStorage.getItem(iter_name)) || 1, '', '', true, true);
					localStorage.setItem(iter_name, (this.id + 1).toString());

					this.Save();
				} else {
					this.CreateData(data.id, data.name, data.price, data.datecr, data.datemd);
				}

				this.Fill();
				this.AutosaveEnable();
			}

			public GetId(): number {
				return this.id;
			}

			private Fill(): void {
				this.$name.val(this.name).trigger('input');
				this.$price.val(this.price).trigger('input');
			}

			private AutosaveEnable(): void {
				this.$name.on('input', this.Commit.bind(this));
				this.$price.on('input', this.Commit.bind(this));
			}

			private CreateData(id: number, name: string, price: string, datecr: string | boolean = false, datemd: string | boolean = false): void {
				this.id = id;
				if (datecr) this.datecr = (datecr === true) ? GetDate() : datecr;

				this.UpdateData(name, price, datemd);
			}

			private UpdateData(name: string, price: string, datemd: string | boolean = false): void {
				if (datemd) this.datemd = (datemd === true) ? GetDate() : datemd;

				this.name = name;
				this.price = price;
			}

			private Commit(): void {
				clearTimeout(this.timer);
				this.timer = setTimeout(this.UpdateDataAndSave.bind(this), this.autosave);
				this.controller.SaveState(PriceListController.STATE_EDIT, 'record');
			}

			private UpdateDataAndSave(): void {
				this.UpdateData(
					this.$name.val().toString(),
					this.$price.val().toString(),
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
						price: this.price
					};
					Site.Common.DB.Put(db, this.controller.GetTableName('record'), data);
					this.controller.SaveState(PriceListController.STATE_SAVE, 'record');
				});
			}

			private QuestionRemove() {
				Site.Common.Window.Interactive(Site.Common.GetMessageBlock('Удалить запись?'), null, [['yes', 'Да'], ['no', 'Нет']], this.Remove.bind(this));
			}

			private Remove(): void {
				Site.Common.DB.Connect().then((db: IDBDatabase) => {
					Site.Common.DB.Delete(db, this.controller.GetTableName('record'), this.id);
				});

				this.table.RemoveRecord(this.id);
				this.$tr.remove();
			}

		}

	}
}