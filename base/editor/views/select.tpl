<?php

	namespace Base\Templates\Editor;

	use Base\Editor\Editor;
	use Base\Templates\Buffering;

	abstract class Select {

		public static function ToVar(Editor $editor, array $fields, array $items, array $ext, string $title, array $navigate, array $manage): string {
			Buffering::Start();
			self::Render($editor, $fields, $items, $ext, $title, $navigate, $manage);
			return Buffering::Read();
		}

		public static function Render(Editor $editor, array $fields, array $items, array $ext, string $title, array $navigate, array $manage): void {
			$pages = $editor->Pages($ext['page'] ?? []);
		?>
			<div class = "navigate">
				<?php foreach ($navigate as $func) echo $func(); ?>
			</div>
			<h1><?= $title; ?></h1>
			<?= $pages; ?>
			<table class = "select">
				<thead>
					<tr>
						<?php foreach ($fields as $field) { ?>
							<th><?= $field->GetTitle(); ?></th>
						<?php } ?>
						<?php if ($manage) { ?><th colspan = "<?= count($manage); ?>">Управление</th><?php } ?>
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
							<?php foreach ($manage as $func) { ?>
								<td><?= $func($item); ?></td>
							<?php } ?>
						</tr>
					<?php } ?>
				</tbody>
			</table>
			<?= $pages; ?>
		<?php }

	}