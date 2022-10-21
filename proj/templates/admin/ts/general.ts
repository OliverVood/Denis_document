namespace Admin {
	export namespace General {

		export function RenderCheck(data: {state: number, name: string, fields: Object}[]) {
			//to -> main (ввести понятия секции в Admin)
			let $title = $('<h1/>').text('Проверка базы данных');
			let $table = $('<table/>');
			let $tbody = $('<tbody/>');
			$table.append(
				$('<thead/>').append(
					$('<tr/>').append(
						$('<th/>').text('Таблицы'),
						$('<th/>').text('Поля'),
						$('<th/>'),
						$('<th/>').text('Ошибка')
					)
				),
				$tbody
			);
			for (let i in data) {
				// if (data[i].state < 1)
				$tbody.append(
					$('<tr/>').append(
						$('<td/>').text(data[i].name),
						$('<td/>').text('-'),
						$('<td/>'),
						$('<td/>').text('Ошибка')
					)
				);
				console.log(data[i]);
			}
			$('main').append($title, $table);
		}

	}
}