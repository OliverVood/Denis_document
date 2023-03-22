<?php

	namespace Base\Templates\Editor;

	use Base\Editor\Editor;
	use Base\Templates\Template;
	use Base\Templates\HTML\Element\Form;
	use Base\Templates\HTML\Element\Text;

	abstract class Update {

		public static function ToVar(Editor $editor, int $id, array $fields, array $item, array $data, string $title): string {
			Template::Start();
			self::Render($editor, $id, $fields, $item, $data, $title);
			return Template::Read();
		}

		public static function Render(Editor $editor, int $id, array $fields, array $item, array $data, string $title): void {
			$form = new Form($data);
		?>
			<div class = "navigate">
				<?php foreach ($editor->navigateUpdate as $navigate) echo $navigate($editor->params); ?>
			</div>
			<h1><?= $title; ?></h1>
		<?php
			$form->Begin($editor->do_update->GetPath());
			Text::Render('id', $id, ['type' => 'hidden']);
			foreach ($editor->params as $name => $params) Text::Render($name, $params, ['type' => 'hidden']);
			foreach ($fields as $name => $field) if ($field['skin'] == 'hidden') $form->Element('hidden', $name, $item[$name]);
		?>
			<table class = "update">
				<tbody>
				<?php foreach ($fields as $name => $field) { if ($field['skin'] == 'hidden') continue; ?>
					<tr>
						<th><?= $field['name']; ?>:</th>
						<td><?php $form->Element($field['skin'], $name, $item[$name] ?? '', $fields['params'] ?? []); ?></td>
					</tr>
				<?php } ?>
				</tbody>
			</table>
			<?php $form->Submit('Изменить', $editor->do_update->GetClick()); $form->End(); ?>
		<?php }

	}