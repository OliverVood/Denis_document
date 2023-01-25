<?php

	namespace Base\Templates\Editor;

	use Base\Editor\Editor;
	use Base\Templates\View;
	use Base\Templates\HTML\Element\Form;
	use Base\Templates\HTML\Element\Text;

	class Update extends View {

		public function ToVar(Editor $editor, int $id, array $fields, array $item, array $data, string $title): string {
			$this->Start();
			$this->Render($editor, $id, $fields, $item, $data, $title);
			return $this->Read();
		}

		public function Render(Editor $editor, int $id, array $fields, array $item, array $data, string $title) {
			$form = new Form($data);
		?>
			<h1><?= $title; ?></h1>
		<?php
			$form->Begin($editor->do_update->GetPath());
			Text::object()->Render('id', $id, ['type' => 'hidden']);
			foreach ($fields as $name => $field) if ($field['skin'] == 'hidden') $form->Element('hidden', $name, $item[$name]);
		?>
			<table class = "update">
				<tbody>
				<?php foreach ($fields as $name => $field) { if ($field['skin'] == 'hidden') continue; ?>
					<tr>
						<th><?= $field['name']; ?>:</th>
						<td><?php $form->Element($field['skin'], $name, $item[$name], $fields['params'] ?? []); ?></td>
					</tr>
				<?php } ?>
				</tbody>
			</table>
			<?php $form->Submit(); $form->End(); ?>
		<?php }

	}