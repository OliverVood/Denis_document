<?php

	namespace Base\Templates\Editor;

	use Base\Templates\HTML\Element\Form;
	use Base\Templates\HTML\Element\Text;
	use Base\Templates\View;

	class Create extends View {

		public function ToVar(array $fields, array $data, string $title): string {
			$this->Start();
			$this->Render($fields, $data, $title);
			return $this->Read();
		}

		public function Render(array $fields, array $data, string $title) {
			$form = new Form($data);
		?>
			<h1><?= $title; ?></h1>
			<?php
				$form->Begin('/news/do_create');//TODO
				foreach ($fields as $name => $field) if ($field['skin'] == 'hidden') Text::object()->Render($name, $field['value'], ['type' => 'hidden'])
			?>
			<table class = "create">
				<tbody>
					<?php foreach ($fields as $name => $field) { if ($field['skin'] == 'hidden') continue; ?>
						<tr>
							<th><?= $field['name']; ?>:</th>
							<td><?php $form->Element($field['skin'], $name, $field['value'], $fields['params'] ?? []); ?></td>
						</tr>
					<?php } ?>
				</tbody>
			</table>
			<?php $form->Submit(); $form->End(); ?>
		<?php }

	}