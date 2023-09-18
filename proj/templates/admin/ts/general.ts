namespace Admin {
	export namespace General {

		type TypeField = { name: string, action: number, error: string, details: string }[];
		type TypeTable = { name: string, action: number, error: string, fields?: TypeField }[];

		export class Render {

			public static ToMain(data: Object) {
				if (data['message']) alert(data['message']);
				Admin.Common.Layout.main.Fill(data['html']);
			}

			public static CheckDB(data: TypeTable) {
				Admin.Common.Layout.main.Fill(
					$('<h1/>').text('Проверка базы данных'),
					data.length ? Render.Form(data) : Render.Empty()
				);
			}

			private static Form(data) {
				/* Elements */
				let $form = $('<form/>', {action: '/db/make'});//TODO Разработать систему экшинов
				let $table = $('<table/>', {class: 'select'});
				let $tbody = $('<tbody/>');
				let $checkbox = $('<input/>', {type: 'checkbox'});
				let $submit = $('<input/>', {type: 'submit', value: 'Исправить'});

				/* Handlers */
				let OnSelectAll = () => {
					$('table input[type="checkbox"]').prop('checked', $checkbox.is(':checked'));
				}

				let OnSubmit = (e) => {
					Base.Common.Query.SubmitFormEvent(e, function (data) {
						Admin.General.Render.CheckDB(data);
					});
					return false;
				}

				/* Events */
				$checkbox.on('click', OnSelectAll);
				$submit.on('click', OnSubmit);

				/* Building DOM */
				$form.append(
					$table.append(
						$('<thead/>').append(
							$('<tr/>').append(
								$('<th/>').text('Таблица'),
								$('<th/>').text('Поле'),
								$('<th/>').append(
									$checkbox
								),
								$('<th/>').text('Ошибка')
							)
						),
						$tbody
					),
					$submit
				);

				Render.Tables($tbody, data);

				return $form;
			}

			private static Tables($tbody, tables) {
				for (let i in tables) Render.Table($tbody, tables[i]);
			}

			private static Table($tbody, table) {
				/* Elements */
				let $checkbox = $('<input/>', {type: 'checkbox', name: `tables[${table.name}][action]`, value: table.action});

				/* Handlers */
				let OnSelectTable = () => {
					$(`input[name^="tables[${table.name}]["]`).prop('checked', $checkbox.is(':checked'));
				}

				/* Events */
				$checkbox.on('click', OnSelectTable);

				/* Building DOM */
				$tbody.append(
					$('<tr/>').append(
						$('<td/>').text(table.name),
						$('<td/>').text('-'),
						$('<td/>').append(
							$checkbox
						),
						$('<td/>').text(table.error)
					)
				);

				if (table.fields) Render.Fields($tbody, table.name, table.fields);
			}

			private static Fields($tbody, tablename, fields) {
				for (let i in fields) Render.Field($tbody, tablename, fields[i]);
			}

			private static Field($tbody, tablename, field) {
				/* Elements */
				let $checkbox = $('<input/>', {type: 'checkbox', name: `tables[${tablename}][fields][${field.name}][action]`, value: field.action});
				let textError = field.error + ((field.details) ? ` (${field.details})` : '');

				/* Handlers */
				let OnSelectField = () => {//TODO Если не выбрано ни одно
					if ($checkbox.is(':checked')) $(`input[name^="tables[${tablename}][action]"]`).prop('checked', true);
				}

				/* Events */
				$checkbox.on('click', OnSelectField);

				/* Building DOM */
				$tbody.append(
					$('<tr/>').append(
						$('<td/>').text(tablename),
						$('<td/>').text(field.name),
						$('<td/>').append(
							$checkbox
						),
						$('<td/>').text(textError)
					)
				);
			}

			private static Empty() {
				return $('<h3>').text('База данных исправна.');
			}

		}

		type StructurePrimaryKey	= { name: string, type: 'primary'; fields: string[]; }
		type StructureForeignKey	= { name: string, type: 'foreign'; fields: string[]; references_table: string, references_fields: string[], relationship_from: number, relationship_to: number }
		type StructureKey<T>		= T;
		type StructureField			= { name: string, type: string; description: string; };
		type StructureTable			= { name: string, description: string, params: {[key: string]: string}, fields: StructureField[], keys: (StructureKey<StructurePrimaryKey>|StructureKey<StructureForeignKey>)[] };
		type StructureDB			= { name: string, tables: StructureTable[] };
		type DisplayMode			= 'name' | 'description';
		type ForeignReferences		= { table: Table, fields: string[], relationship: number };

		export class Structure {
			db						: DB;
			display_mode			: DisplayMode;

			$structure				: HTMLElement;
			$panel					: HTMLDivElement;
			$display				: HTMLDivElement;

			constructor(data: StructureDB) {
				this.$structure		= document.getElementById('structure');
				this.db 			= new DB(data);
				this.display_mode	= 'description';

				this.$panel			= document.createElement('div'); this.$panel.className			= 'panel';
				this.$display		= document.createElement('div'); this.$display.className		= 'display';
				this.SwitchDisplayMode();

				this.$display.addEventListener('click', () => this.SwitchDisplayMode());
				DragAndDrop(this.$panel, this.$panel);

				this.$panel.append(this.$display);
				this.$structure.append(this.$panel);
			}

			private SwitchDisplayMode(): void {
				this.$display.innerText = (this.display_mode === 'name') ? 'D' : 'N';
				this.display_mode = (this.display_mode === 'name') ? 'description' : 'name';
				this.$structure.className = (this.display_mode === 'name') ? 'display_description' : 'display_name';
			}

		}

		class DB {
			tables					: {[key: string]: Table};

			constructor(data: StructureDB) {
				this.tables			= {};
				for (const i in data.tables) this.tables[data.tables[i].name] = new Table(data.tables[i]);
				for (const i in data.tables) for (const j in data.tables[i].keys) {
					// console.log(data.tables[i].keys);
					// console.log(data.tables[i].keys[j]);
					switch (data.tables[i].keys[j].type) {
						case 'primary': this.SetPrimaryKey(data.tables[i].keys[j].name, this.tables[data.tables[i].name], data.tables[i].keys[j].fields); break;
						case 'foreign': this.SetForeignKey(data.tables[i].keys[j].name, this.tables[data.tables[i].name], data.tables[i].keys[j].fields, data.tables[i].keys[j].relationship_from, {table: this.tables[data.tables[i].keys[j].references_table] ,fields: data.tables[i].keys[j].references_fields , relationship: data.tables[i].keys[j].relationship_to }); break;
					}
				}
			}

			private SetPrimaryKey(name: string, table: Table, fields: string[]): void {
				let fields_objs = [];
				for (const i in fields) fields_objs.push(table.fields[fields[i]]);
				new Primary(name, table, fields_objs);
			}

			// StructureKey<StructureForeignKey>
			private SetForeignKey(name: string, table: Table, fields: string[], relationship: number, references: ForeignReferences): void {
				console.log(references);
				let fields_objs = [];
				let references_fields_objs = [];
				for (const i in fields) fields_objs.push(table.fields[fields[i]]);
				for (const i in references.fields) references_fields_objs.push(references.table.fields[references.fields[i]]);
				new Foreign(name, table, fields_objs, relationship, {table: references.table, fields: references_fields_objs, relationship: references.relationship});
			}

		}

		class Table {
			public fields						: {[key: string]: Field};
			private readonly $table				: HTMLDivElement;
			private readonly $drag				: HTMLDivElement;
			private readonly $header			: HTMLDivElement;
			private readonly $title				: HTMLDivElement;
			private readonly $name				: HTMLDivElement;
			private readonly $description		: HTMLDivElement;
			private readonly $menu				: HTMLDivElement;
			private readonly $rows				: HTMLDivElement;
			private readonly $keys				: HTMLDivElement;

			constructor(data: StructureTable) {
				this.fields						= {};

				this.$table 					= document.createElement('div'); this.$table.className			= 'table';
				this.$drag 						= document.createElement('div'); this.$drag.className			= 'drag';
				this.$header 					= document.createElement('div'); this.$header.className			= 'header';
				this.$title 					= document.createElement('div'); this.$title.className			= 'title';
				this.$name 						= document.createElement('div'); this.$name.className			= 'name';
				this.$description 				= document.createElement('div'); this.$description.className	= 'description';
				this.$menu 						= document.createElement('div'); this.$menu.className			= 'menu';
				this.$rows 						= document.createElement('div'); this.$rows.className			= 'rows';
				this.$keys 						= document.createElement('div'); this.$keys.className			= 'keys';

				this.$name.innerText			= data.name;
				this.$description.innerText		= data.description;
				this.$menu.innerText			= '▼';

				this.$table.append(this.$drag, this.$header, this.$rows, this.$keys);
				this.$header.append(this.$title, this.$menu);
				this.$title.append(this.$name, this.$description);

				for (const i in data['fields']) this.fields[data['fields'][i]['name']] = new Field(this.$rows, data['fields'][i]);

				document.getElementById('structure').append(this.$table);

				DragAndDrop(this.$drag, this.$table, {top: 0, left: 0});
			}

			public AddKey(type: string, name: string, key: Key): HTMLDivElement {
				let $wrap = document.createElement('div');
				let $type = document.createElement('div'); $type.className = 'type'; $type.innerText = type;
				let $name = document.createElement('div'); $name.className = 'name'; $name.innerText = name;

				this.$keys.append($wrap);
				$wrap.append($type, $name);

				$wrap.addEventListener('click', () => { key.Display(); });

				return $wrap;
			}

		}

		class Field {
			private readonly $wrap				: HTMLDivElement;
			private readonly $name				: HTMLDivElement;
			private readonly $description		: HTMLDivElement;
			private readonly $key				: HTMLDivElement;

			static ER_RELATIONSHIP = {
				1: 'one',
				2: 'many',
				3: 'only_one',
				4: 'zero_or_one',
				5: 'one_or_many',
				6: 'zero_or_many'
			};

			constructor($rows: HTMLDivElement, data: StructureField) {
				this.$wrap						= document.createElement('div');
				this.$name						= document.createElement('div'); this.$name.className			= 'name';
				this.$description				= document.createElement('div'); this.$description.className	= 'description';
				this.$key						= document.createElement('div'); this.$key.className			= 'key';

				this.$name.innerText			= data['name'];
				this.$description.innerText		= data['description'];

				this.$wrap.append(this.$name, this.$description, this.$key);
				$rows.append(this.$wrap);
			}

			public SetPrimaryKey(): void {
				this.$key.innerText = 'Pr';
				this.$wrap.classList.add('key', 'primary');
			}

			public UnsetPrimaryKey(): void {
				this.$key.innerText = '';
				this.$wrap.classList.remove('key', 'primary');
			}

			public SetForeignKey(relationship: number): void {
				this.$key.innerText = 'Fr';
				this.$wrap.classList.add('key', 'foreign', Field.ER_RELATIONSHIP[relationship]);
			}

			public UnsetForeignKey(relationship: number): void {
				this.$key.innerText = '';
				this.$wrap.classList.remove('key', 'foreign', Field.ER_RELATIONSHIP[relationship]);
			}

			public SetReferencesKey(relationship: number): void {
				this.$key.innerText = '*';
				this.$wrap.classList.add('key', 'references', Field.ER_RELATIONSHIP[relationship]);
			}

			public UnsetReferencesKey(relationship: number): void {
				this.$key.innerText = '';
				this.$wrap.classList.remove('key', 'references', Field.ER_RELATIONSHIP[relationship]);
			}

		}

		class Key {
			name								: string
			table								: Table;
			fields								: Field[];
			display								: boolean;

			$key								: HTMLDivElement;

			constructor(name: string, table: Table, fields: Field[]) {
				this.table						= table;
				this.name						= name;
				this.fields						= fields;
				this.display					= false;
			}

			public Display(): void {  }

		}

		class Primary extends Key {

			constructor(name: string, table: Table, fields: Field[]) {
				super(name, table, fields);

				this.$key = this.table.AddKey('primary', this.name, this);
			}

			public Display(): void {
				this.display = !this.display;
				if (this.display) {
					this.$key.classList.add('active');
					for (const i in this.fields) this.fields[i].SetPrimaryKey();
				} else {
					this.$key.classList.remove('active');
					for (const i in this.fields) this.fields[i].UnsetPrimaryKey();
				}
			}

		}

		class Foreign extends Key {
			relationship						: number
			references							: {table: Table, fields: Field[], relationship: number};

			constructor(name: string, table: Table, fields: Field[], relationship: number, references: {table: Table, fields: Field[], relationship: number}) {
				super(name, table, fields);

				this.relationship				= relationship;
				this.references					= references;

				this.$key = this.table.AddKey('foreign', this.name, this);
			}

			public Display(): void {
				this.display = !this.display;
				if (this.display) {
					this.$key.classList.add('active');
					for (const i in this.fields) this.fields[i].SetForeignKey(this.relationship);
					for (const i in this.references.fields) this.references.fields[i].SetReferencesKey(this.references.relationship);

				} else {
					this.$key.classList.remove('active');
					for (const i in this.fields) this.fields[i].UnsetForeignKey(this.relationship);
					for (const i in this.references.fields) this.references.fields[i].UnsetReferencesKey(this.references.relationship);
				}
			}

		}

		function DragAndDrop(drag: HTMLElement, container: HTMLElement, scope: { top?: number, right?: number, bottom?: number, left?: number } = {}) {
			let scope_top = (scope.top !== undefined) ? scope.top : null;
			let scope_right = (scope.right !== undefined) ? scope.right : null;
			let scope_bottom = (scope.bottom !== undefined) ? scope.bottom : null;
			let scope_left = (scope.left !== undefined) ? scope.left : null;
			drag.onmousedown = function(event) {
				if (!drag || !container) return;

				container.style.zIndex = '1';

				document.onmousemove = function(event) {
					Move(event);
				};

				document.onmouseup = function() {
					document.onmousemove = null;
					document.onmouseup = null;
				};

				function Move(event) {
					let delta_left = parseInt(container.style.left || getComputedStyle(container)['left']);
					if (isNaN(delta_left)) delta_left = 0;
					let left = delta_left + event.movementX;

					if (scope_right !== null) {
						let width = parseFloat(container.style.width || getComputedStyle(container)['width']);
						if (left > (scope_right - width)) left = scope_right - Math.ceil(width);
					}
					if (scope_left !== null && left < scope_left) left = scope_left;

					let delta_top = parseInt(container.style.top || getComputedStyle(container)['top']);
					if (isNaN(delta_top)) delta_top = 0;
					let top = delta_top + event.movementY;

					if (scope_bottom !== null) {
						let height = parseFloat(container.style.height || getComputedStyle(container)['height']);
						if (top > (scope_bottom - height)) top = scope_bottom - Math.ceil(height);
					}
					if (scope_top !== null && top < scope_top) top = scope_top;

					container.style.left = `${left}px`;
					container.style.top = `${top}px`;
				}
			}

		}

	}
}