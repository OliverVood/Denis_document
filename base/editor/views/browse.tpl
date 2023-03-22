<?php

	namespace Base\Templates\Editor;

	use Base\Editor\Editor;
	use Base\Templates\Template;

	abstract class Browse {

		public static function ToVar(Editor $editor, int $id, array $fields, array $item, array $data, string $title): string {
			Template::Start();
			self::Render($editor, $id, $fields, $item, $data, $title);
			return Template::Read();
		}

		public static function Render(Editor $editor, int $id, array $fields, array $item, array $data, string $title): void { ?>
			<div class = "navigate">
				<?php foreach ($editor->navigateBrowse as $navigate) echo $navigate($editor->params); ?>
			</div>
			<h1><?= $title; ?></h1>
			<table class = "browse">
				<tbody>
				<?php foreach ($fields as $name => $field) { ?>
					<tr>
						<th><?= $field['name']; ?>:</th>
						<td><?= nl2br(htmlspecialchars($item[$name])); ?></td>
					</tr>
				<?php } ?>
				</tbody>
			</table>
		<?php }

	}