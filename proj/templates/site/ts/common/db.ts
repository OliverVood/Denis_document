namespace Site {
	export namespace Common {

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
						store.createIndex('did', 'did');
					}
					if (!result.objectStoreNames.contains('estimate_record')) {
						let store = result.createObjectStore('estimate_record', {keyPath: 'id'});
						store.createIndex('tid', 'tid');
					}

					if (!result.objectStoreNames.contains('certificate')) result.createObjectStore('certificate', {keyPath: 'id'});
					if (!result.objectStoreNames.contains('certificate_table')) {
						let store = result.createObjectStore('certificate_table', {keyPath: 'id'});
						store.createIndex('did', 'did');
					}
					if (!result.objectStoreNames.contains('certificate_record')) {
						let store = result.createObjectStore('certificate_record', {keyPath: 'id'});
						store.createIndex('tid', 'tid');
					}


					if (!result.objectStoreNames.contains('price_list')) result.createObjectStore('price_list', {keyPath: 'id'});
					if (!result.objectStoreNames.contains('price_list_table')) {
						let store = result.createObjectStore('price_list_table', {keyPath: 'id'});
						store.createIndex('did', 'did');
					}
					if (!result.objectStoreNames.contains('price_list_record')) {
						let store = result.createObjectStore('price_list_record', {keyPath: 'id'});
						store.createIndex('tid', 'tid');
					}
				});
			}

		}

		DB.CheckStructure();

	}
}