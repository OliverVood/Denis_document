<?php

	namespace Proj\Admin\Templates\Composition;

	use Base\Templates\Buffering;
	use Proj\Admin\Actions;

	abstract class Models {

		public static function ToVar(array $units, array $routes): string {
			Buffering::Start();
			self::Render($units, $routes);
			return Buffering::Read();
		}

		public static function Render(array $units, array $routes): void { ?>
			<h1>Добавление модели</h1>
			<form action = "<?= Actions\Composition::$create_model->GetPath(); ?>">
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
						<tr>
							<th>Часть:</th>
							<td>
								<?php foreach ($routes as $key => $route) { ?>
									<label><input type = "radio" name = "form[route]" value = "<?= $key; ?>"><?= $route; ?></label>
								<?php } ?>
							</td>
						</tr>
					</tbody>
				</table>
				<input type = "submit" value = "Создать" onclick = "Base.Common.Query.SubmitForm(this); return false;">
			</form>
		<?php }

	}