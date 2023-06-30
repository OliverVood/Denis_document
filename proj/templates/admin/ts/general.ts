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

		type StructureField		= { name: string, type: string; description: string; };
		type StructureTable			= { name: string, description: string, params: {[key: string]: string}, fields: StructureField[] };
		type StructureDB			= { name: string, tables: StructureTable[] };
		type DisplayMode			= 'name' | 'description';

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
			tables					: Table[];

			constructor(data: StructureDB) {
				this.tables			= [];
				for (const i in data['tables']) this.tables.push(new Table(data['tables'][i]));
			}

		}

		class Table {
			private readonly $table				: HTMLDivElement;
			private readonly $drag				: HTMLDivElement;
			private readonly $header			: HTMLDivElement;
			private readonly $title				: HTMLDivElement;
			private readonly $name				: HTMLDivElement;
			private readonly $description		: HTMLDivElement;
			private readonly $menu				: HTMLDivElement;
			private readonly $rows				: HTMLDivElement;

			constructor(data: StructureTable) {
				this.$table 					= document.createElement('div'); this.$table.className			= 'table';
				this.$drag 						= document.createElement('div'); this.$drag.className			= 'drag';
				this.$header 					= document.createElement('div'); this.$header.className			= 'header';
				this.$title 					= document.createElement('div'); this.$title.className			= 'title';
				this.$name 						= document.createElement('div'); this.$name.className			= 'name';
				this.$description 				= document.createElement('div'); this.$description.className	= 'description';
				this.$menu 						= document.createElement('div'); this.$menu.className			= 'menu';
				this.$rows 						= document.createElement('div'); this.$rows.className			= 'rows';

				this.$name.innerText			= data.name;
				this.$description.innerText		= data.description;
				this.$menu.innerText			= '▼';

				this.$table.append(this.$drag, this.$header, this.$rows);
				this.$header.append(this.$title, this.$menu);
				this.$title.append(this.$name, this.$description);

				for (const i in data['fields']) {
					let $wrap				= document.createElement('div');
					let $name				= document.createElement('div'); $name.className			= 'name';
					let $description		= document.createElement('div'); $description.className		= 'description';

					$name.innerText			= data['fields'][i].name;
					$description.innerText	= data['fields'][i].description;

					$wrap.append($name, $description);
					this.$rows.append($wrap);
				}

				document.getElementById('structure').append(this.$table);
			}

		}

	}
}