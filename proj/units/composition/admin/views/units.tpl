<?php

	namespace Proj\Admin\Templates\Composition;

	use Base\Templates\Buffering;
	use Proj\Admin\Actions;

	abstract class Units {

		public static function ToVar(array $units): string {
			Buffering::Start();
			self::Render($units);
			return Buffering::Read();
		}

		public static function Render(array $units): void { ?>
			<h1>Добавление единицы</h1>
			<form action = "<?= Actions\Composition::$create_unit->GetPath(); ?>">
				<h3>Основное</h3>
				<table class = "create">
					<tbody>
						<tr>
							<th>Номер:</th>
							<td><input type = "text" name = "form[id]"></td>
						</tr>
						<tr>
							<th>Название:</th>
							<td><input type = "text" name = "form[name]"></td>
						</tr>
					</tbody>
				</table>
				<h3>Администраторская часть</h3>
				<table class = "create">
					<tbody>
						<tr>
							<th>Точки входа:</th>
							<td>
								<label><input type = "checkbox" name = "form[routes][admin][entries][html]">HTML</label>
								<label><input type = "checkbox" name = "form[routes][admin][entries][xhr]">XHR</label>
							</td>
						</tr>
						<tr>
							<th>Класс ссылок:</th>
							<td>
								<label><input type = "checkbox" name = "form[routes][admin][actions]">Создать</label>
							</td>
						</tr>
						<tr>
							<th>Структура:</th>
							<td>
								<label><input type = "checkbox" name = "form[routes][admin][structure]">Создать</label>
							</td>
						</tr>
						<tr>
							<th>Модель:</th>
							<td>
								<label><input type = "checkbox" name = "form[routes][admin][model]">Создать</label>
							</td>
						</tr>
					</tbody>
				</table>
				<h3>Сайтовая часть</h3>
				<table class = "create">
					<tbody>
					<tr>
						<th>Точки входа:</th>
						<td>
							<label><input type = "checkbox" name = "form[routes][site][entries][html]">HTML</label>
							<label><input type = "checkbox" name = "form[routes][site][entries][xhr]">XHR</label>
						</td>
					</tr>
					<tr>
						<th>Класс ссылок:</th>
						<td>
							<label><input type = "checkbox" name = "form[routes][site][actions]">Создать</label>
						</td>
					</tr>
					<tr>
						<th>Модель:</th>
						<td>
							<label><input type = "checkbox" name = "form[routes][site][model]">Создать</label>
						</td>
					</tr>
					</tbody>
				</table>
				<input type = "submit" value = "Создать" onclick = "Base.Common.Query.SubmitForm(this); return false;">
			</form>
			<h3>Перечень инициализированных единиц</h3>
			<table class = "select">
				<thead>
					<tr>
						<th>#</th>
						<th>Название</th>
					</tr>
				</thead>
				<tbody>
					<?php foreach ($units as ['id' => $id, 'name' => $name]) { ?>
						<tr>
							<td><?= $id; ?></td>
							<td><?= $name; ?></td>
						</tr>
					<?php } ?>
				</tbody>
			</table>
		<?php }

	}