<?php

	namespace Base\Templates\Editor;

	use Base\Editor\Editor;
	use Base\Templates\Buffering;

	abstract class Browse {

		public static function ToVar(Editor $editor, array $fields, int $id, array $item, string $title, array $navigate): string {
			Buffering::Start();
			self::Render($editor, $fields, $id, $item, $title, $navigate);
			return Buffering::Read();
		}

		public static function Render(Editor $editor, array $fields, int $id, array $item, string $title, array $navigate): void { ?>
			<div class = "navigate">
				<?php foreach ($navigate as $func) echo $func(); ?>
			</div>
			<h1><?= $title; ?></h1>
			<table class = "browse">
				<tbody>
					<?php foreach ($fields as $key => $field) { ?>
						<tr>
							<th><?= $field->GetTitle(); ?>:</th>
							<td><?= $field->ToVar($item[$key]); ?></td>
						</tr>
					<?php } ?>
				</tbody>
			</table>
		<?php }

	}