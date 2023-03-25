<?php

	namespace Base\Templates\Editor;

	use Base\Editor\Editor;
	use Base\Templates\Template;

	abstract class Select {

		public static function ToVar(Editor $editor, array $fields, array $items, string $title, array $ext): string {
			Template::Start();
			self::Render($editor, $fields, $items, $title, $ext);
			return Template::Read();
		}

		public static function Render(Editor $editor, array $fields, array $items, string $title, array $ext): void {
			$col = count($editor->manage);
			$pages = $editor->Pages($ext['page'] ?? []);
		?>
			<div class = "navigate">
				<?php foreach ($editor->navigateSelect as $navigate) echo $navigate($editor->params); ?>
			</div>
			<h1><?= $title; ?></h1>
			<?= $pages; ?>
			<table class = "select">
				<thead>
					<tr>
						<?php foreach ($fields as $field) { ?>
							<th><?= $field->GetName(); ?></th>
						<?php } ?>
						<?php if ($col) { ?><th colspan = "<?= $col ?>">Управление</th><?php } ?>
					</tr>
				</thead>
				<tbody>
					<?php foreach ($items as $item) { ?>
					    <tr>
							<?php foreach ($fields as $key => $field) { ?>
								<td>
									<?= $field->ToVar($item[$key]); ?>
								</td>
							<?php } ?>
							<?php foreach ($editor->manage as $manage) { ?>
								<td><?= $manage($editor->params, $item); ?></td>
							<?php } ?>
						</tr>
					<?php } ?>
				</tbody>
			</table>
			<?= $pages; ?>
		<?php }

	}