<?php

	namespace Base\Templates\Editor;

	use Base\Editor\Editor;
	use Base\Editor\Skins\Edit\Hidden;
	use Base\Templates\Buffering;

	abstract class Create {

		public static function ToVar(Editor $editor, array $fields, string $title, array $navigate, array $params): string {
			Buffering::Start();
			self::Render($editor, $fields, $title, $navigate, $params);
			return Buffering::Read();
		}

		public static function Render(Editor $editor, array $fields, string $title, array $navigate, array $params): void { ?>
			<div class = "navigate">
				<?php foreach ($navigate as $func) echo $func(); ?>
			</div>
			<h1><?= $title; ?></h1>
			<form action = "<?= $editor->do_create->GetPath(); ?>">
				<?php
					foreach ($params as $name => $value) (new Hidden('', $name))->Render($value);
					foreach ($fields as $field) if (get_class($field) == 'Base\Editor\Skins\Edit\Hidden') echo $field->ToVar();
				?>
				<table class = "create">
					<tbody>
						<?php foreach ($fields as $field) { if (get_class($field) == 'Base\Editor\Skins\Edit\Hidden') continue; ?>
							<tr>
								<th><?= $field->GetTitle(); ?>:</th>
								<td><?= $field->ToVar(); ?></td>
							</tr>
						<?php } ?>
					</tbody>
				</table>
				<input type = "submit" value = "Создать" onclick = "<?= $editor->do_create->GetClick(); ?>">
			</form>
		<?php }

	}