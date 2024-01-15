<?php

	namespace Proj\Admin\Templates\Composition;

	use Base\Templates\Buffering;
	use Proj\Admin\Actions;

	abstract class Editors {

		public static function ToVar(array $units, array $editors): string {
			Buffering::Start();
			self::Render($units, $editors);
			return Buffering::Read();
		}

		public static function Render(array $units, array $editors): void { ?>
			<h1>Добавление редактора</h1>
			<form action = "<?= Actions\Composition::$create_editor->GetPath(); ?>">
				<h3>Основное</h3>
				<table class = "create">
					<tbody>
						<tr>
							<th>Название:</th>
							<td><input type = "text" name = "form[name]"></td>
						</tr>
						<tr>
							<th>Единица:</th>
							<td>
								<?php foreach ($units as $unit) { ?>
									<label><input type = "radio" name = "form[unit]" value = "<?= $unit['id']; ?>"><?= $unit['name']; ?></label>
								<?php } ?>
							</td>
						</tr>
					</tbody>
				</table>
				<input type = "submit" value = "Создать" onclick = "Base.Common.Query.SubmitForm(this); return false;">
			</form>
			<h3>Перечень инициализированных композиций</h3>
			<table class = "select">
				<thead>
				<tr>
					<th>#</th>
					<th>Название</th>
					<th>Заголовок</th>
					<th>Тип</th>
				</tr>
				</thead>
				<tbody>
				<?php foreach ($units as ['id' => $id, 'name' => $name, 'title' => $title]) { ?>
					<tr>
						<td><?= $id; ?></td>
						<td><?= $name; ?></td>
						<td><?= $title; ?></td>
						<td><?= 'Единица'; ?></td>
					</tr>
				<?php } ?>
				<?php foreach ($editors as ['id' => $id, 'name' => $name, 'title' => $title]) { ?>
					<tr>
						<td><?= $id; ?></td>
						<td><?= $name; ?></td>
						<td><?= $title; ?></td>
						<td><?= 'Редактор'; ?></td>
					</tr>
				<?php } ?>
				</tbody>
			</table>
		<?php }

	}