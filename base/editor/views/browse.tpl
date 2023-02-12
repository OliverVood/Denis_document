<?php

	namespace Base\Templates\Editor;

	use Base\Editor\Editor;
	use Base\Templates\View;

	class Browse extends View {

		public function ToVar(Editor $editor, int $id, array $fields, array $item, array $data, string $title): string {
			$this->Start();
			$this->Render($editor, $id, $fields, $item, $data, $title);
			return $this->Read();
		}

		public function Render(Editor $editor, int $id, array $fields, array $item, array $data, string $title) { ?>
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