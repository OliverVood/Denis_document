<?php

	namespace Base\Templates\Editor;

	use Base\Editor\Editor;
	use Base\Editor\Skins\Edit\Hidden;
	use Base\Templates\Buffering;

	abstract class Update {

		public static function ToVar(Editor $editor, array $fields, int $id, array $item, string $title, array $navigate, array $params): string {
			Buffering::Start();
			self::Render($editor, $fields, $id, $item, $title, $navigate, $params);
			return Buffering::Read();
		}

		public static function Render(Editor $editor, array $fields, int $id, array $item, string $title, array $navigate, array $params): void { ?>
			<div class = "navigate">
				<?php foreach ($navigate as $func) echo $func(); ?>
			</div>
			<h1><?= $title; ?></h1>
			<form action = "<?= $editor->do_update->GetPath(); ?>">
				<?php
					foreach ($params as $name => $value) (new Hidden('', $name))->Render($value);
					(new Hidden('id', 'id'))->Render($id);
					foreach ($fields as $key => $field) if (get_class($field) == 'Base\Editor\Skins\Edit\Hidden') echo $field->ToVar($item[$key] ?? null);
				?>
				<table class = "update">
					<tbody>
					<?php foreach ($fields as $key => $field) { if (get_class($field) == 'Base\Editor\Skins\Edit\Hidden') continue; ?>
						<tr>
							<th><?= $field->GetTitle(); ?>:</th>
							<td><?= $field->ToVar($item[$key] ?? null); ?></td>
						</tr>
					<?php } ?>
					</tbody>
				</table>
				<input type = "submit" value = "<?= $editor->btnUpdate; ?>" onclick = "<?= $editor->do_update->GetClick(); ?>">
			</form>
		<?php }

	}