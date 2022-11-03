namespace Admin {
	export namespace General {

		type TypeField = { name: string, state: number, error: string, details: string }[];
		type TypeTable = { name: string, state: number, error: string, fields?: TypeField }[];

		export function RenderCheck(data: TypeTable) {
			/* Elements */
			let $title = $('<h1/>').text('Проверка базы данных');
			let $form = $('<form/>', {action: '/db/make'});
			let $table = $('<table/>');
			let $tbody = $('<tbody/>');
			let $checkbox = $('<input/>', {type: 'checkbox'});
			let $submit = $('<input/>', {type: 'submit', value: 'Исправить'});

			/* Events */
			$checkbox.on('click', function () {
				$('table input[type="checkbox"]').prop('checked', $checkbox.is(':checked'));
			});
			$submit.on('click', function () {
				Base.Common.Query.SendForm($submit.closest('form'), function () {
					console.log('!!!');
				});
				return false;
			})

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
			for (let i in data) {
				$tbody.append(
					GetTable(data[i])
				);
				if (data[i].fields)
					for (let j in data[i].fields)
						$tbody.append(
							GetField(data[i].name, data[i].fields[j])
						);
			}
			Admin.Common.Layout.main.Fill($title, $form);

			function GetTable(table) {
				let $checkbox = $('<input/>', {type: 'checkbox', name: `tables[${table.name}][state]`, value: table.state})
				$checkbox.on('click', function () {
					$(`input[name^="tables[${table.name}]["]`).prop('checked', $checkbox.is(':checked'));
				})
				return $('<tr/>').append(
					$('<td/>').text(table.name),
					$('<td/>').text('-'),
					$('<td/>').append(
						$checkbox
					),
					$('<td/>').text(table.error)
				);

			}

			function GetField (tablename, field) {
				return $('<tr/>').append(
					$('<td/>').text(tablename),
					$('<td/>').text(field.name),
					$('<td/>').append(
						$('<input/>', {type: 'checkbox', name: `tables[${tablename}][fields][${field.name}]`, value: field.state})
					),
					$('<td/>').text(field.error)
				);
			}
		}

	}
}