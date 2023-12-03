<?php

	namespace Proj\Admin\Templates\Composition;

	use Base\Templates\Buffering;
	use Proj\Admin\Actions;

	abstract class Editors {

		public static function ToVar(array $editors, array $units): string {
			Buffering::Start();
			self::Render($editors, $units);
			return Buffering::Read();
		}

		public static function Render(array $editors, array $units): void { ?>
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
			<h3>Перечень инициализированных редакторов</h3>
			<table class = "select">
				<thead>
					<tr>
						<th>Название</th>
					</tr>
				</thead>
				<tbody>
					<?php foreach ($editors as ['name' => $name]) { ?>
						<tr>
							<td><?= $name; ?></td>
						</tr>
					<?php } ?>
				</tbody>
			</table>
		<?php }

	}