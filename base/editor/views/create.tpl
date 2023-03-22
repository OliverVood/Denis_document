<?php

	namespace Base\Templates\Editor;

	use Base\Editor\Editor;
	use Base\Templates\Template;
	use Base\Templates\HTML\Element\Form;
	use Base\Templates\HTML\Element\Text;

	abstract class Create {

		public static function ToVar(Editor $editor, array $fields, array $data, string $title): string {
			Template::Start();
			self::Render($editor, $fields, $data, $title);
			return Template::Read();
		}

		public static function Render(Editor $editor, array $fields, array $data, string $title): void {
			$form = new Form($data);
		?>
			<div class = "navigate">
				<?php foreach ($editor->navigateCreate as $navigate) echo $navigate($editor->params); ?>
			</div>
			<h1><?= $title; ?></h1>
			<?php
				$form->Begin($editor->do_create->GetPath());
				foreach ($editor->params as $name => $params) Text::Render($name, $params, ['type' => 'hidden']);
				foreach ($fields as $name => $field) if ($field['skin'] == 'hidden') $form->Element('hidden', $name, $field['default'])
			?>
			<table class = "create">
				<tbody>
					<?php foreach ($fields as $name => $field) { if ($field['skin'] == 'hidden') continue; ?>
						<tr>
							<th><?= $field['name']; ?>:</th>
							<td><?php $form->Element($field['skin'], $name, $field['default'] ?? '', $field['params'] ?? []); ?></td>
						</tr>
					<?php } ?>
				</tbody>
			</table>
			<?php $form->Submit('Создать', $editor->do_create->GetClick()); $form->End(); ?>
		<?php }

	}