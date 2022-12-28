namespace Site {
	export namespace Common {

		export class Layout extends Base.Common.Layout {
			public static header	: Base.Common.Section;
			public static main		: Base.Common.Section;
			public static footer	: Base.Common.Section;

			public static Initialization(): void {
				Layout.header = new Base.Common.Section($('header'));
				Layout.main = new Base.Common.Section($('main'));
				Layout.footer = new Base.Common.Section($('footer'));
			}

		}

		export class UIDate {

			static Today(): string {
				let d = new Date();
				let day = d.getDate();
				let month = d.getMonth() + 1;
				let year = d.getFullYear();

				return `${year}-${month}-${day}`;
			}

		}

		export class DB {
			static VERSION = 1;
			static NAME = 'desktop';
			static EXECUTE = '';

			static Connect(execute = ['transaction']): Promise<any> {

				return new Promise((resolve, reject) => {
					let request = window.indexedDB.open(DB.NAME, DB.VERSION);

					/* Check structure */
					request.onupgradeneeded = event => {
						DB.EXECUTE = 'version';
						if (execute.includes('version')) resolve(event.target.result);
					}

					request.onsuccess = event => {
						request.result.onversionchange = () => {
							request.result.close();
							alert("База данных устарела, пожалуйста, перезагрузите страницу.");
						};

						DB.EXECUTE = 'transaction';
						if (execute.includes('transaction')) resolve(event.target.result);
					}

					request.onerror = event => {
						console.error("Error: ", event, request.error);
						reject(event);
					}

					request.onblocked = () => {
						alert("База данных заблокированна, пожалуйста, закройте другие вкладки сайта и перезагрузите страницу.");
					}

				});
			}

			static Get(db: IDBDatabase, storeName: string, id: number): Promise<any> {
				return new Promise((resolve, reject) => {
					let transaction = db.transaction(storeName, 'readonly');
					let store = transaction.objectStore(storeName);
					let request = store.get(id);

					request.onsuccess = event => {
						resolve(event.target.result);
					}

					request.onerror = event => {
						console.error("Error: ", event, request.error);
						reject(event);
					}
				});
			}

			static Cursor(db: IDBDatabase, storeName: string, funcContinue: Function, funcEnd?: Function)/*: Promise<any>*/ {
				// return new Promise((resolve, reject) => {
					let transaction = db.transaction(storeName, 'readonly');
					let store = transaction.objectStore(storeName);
					let request = store.openCursor();

					request.onsuccess = event => {
						let cursor = event.target.result;

						if (!cursor) { if (funcEnd) funcEnd(); return; }

						funcContinue(cursor);
						cursor.continue();
					}

					request.onerror = event => {
						console.error("Error: ", event, request.error);
						// reject(event);
					}
				// });
			}

			static CursorIndex(db: IDBDatabase, storeName: string, indexName: string, range: IDBKeyRange, funcContinue: Function, funcEnd?: Function)/*: Promise<any>*/ {
				// return new Promise((resolve, reject) => {
					let transaction = db.transaction(storeName, 'readonly');
					let store = transaction.objectStore(storeName);
					let index = store.index(indexName);
					let request = index.openCursor(range);

					request.onsuccess = event => {
						let cursor = event.target.result;

						if (!cursor) { if (funcEnd) funcEnd(); return; }

						funcContinue(cursor);
						cursor.continue();
					}

					request.onerror = event => {
						console.error("Error: ", event, request.error);
						// reject(event);
					}
				// });
			}

			static Put(db: IDBDatabase, storeName: string, data: any): void {
				let transaction = db.transaction(storeName, 'readwrite');
				let store = transaction.objectStore(storeName);
				store.put(data);
			}

			static Delete(db: IDBDatabase, storeName: string, id: number): void {
				let transaction = db.transaction(storeName, 'readwrite');
				let store = transaction.objectStore(storeName);
				store.delete(id);
			}

			static CheckStructure(): void {
				DB.Connect(['version']).then((result: IDBDatabase) => {
					if (!result.objectStoreNames.contains('estimate')) result.createObjectStore('estimate', {keyPath: 'id'});
					if (!result.objectStoreNames.contains('estimate_table')) {
						let store = result.createObjectStore('estimate_table', {keyPath: 'id'});
						store.createIndex('eid', 'eid');
					}
					if (!result.objectStoreNames.contains('estimate_record')) {
						let store = result.createObjectStore('estimate_record', {keyPath: 'id'});
						store.createIndex('tid', 'tid');
					}
				});
			}

		}

		DB.CheckStructure();

		export class Menu {
			jq_body			: JQuery;
			jq_wrap			: JQuery;
			jq_close		: JQuery;
			jq_menu_1		: JQuery;
			jq_menu_3		: JQuery;

			constructor() {
				/*  */
				this.jq_body = $('body');
				this.jq_wrap = $('<div/>', {class: 'view site full_menu'});
				this.jq_close = $('<div/>', {class: 'close'});
				this.jq_menu_1 = $('<div/>', {class: 'menu m1'});
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
					this.jq_menu_3.append(
						$('<div/>').append(
							$('<div/>').text('Документы'),
							$('<div/>').append(
								$('<div/>').text('Управление товарами'),
								$('<div/>').text('Вава'),
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