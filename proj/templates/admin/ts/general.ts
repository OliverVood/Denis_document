namespace Admin {
	export namespace General {

		export function RenderCheck(data :{ name :string, state :number, error ?:string, fields ?:Object }[]) {
			//to -> main (ввести понятия секции в Admin)
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
				Base.Common.RequestForm($submit.closest('form'), function () {
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
			$('main').empty().append($title, $form);

			function GetTable(table) {
				let $checkbox = $('<input/>', {type: 'checkbox', name: `make[${table.name}]`, value: 1})
				$checkbox.on('click', function () {
					$(`input[name^="make[${table.name}]["]`).prop('checked', $checkbox.is(':checked'));
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
						$('<input/>', {type: 'checkbox', name: `make[${tablename}][${field.name}]`, value: 1})
					),
					$('<td/>').text(field.error)
				);
			}
		}

	}
}