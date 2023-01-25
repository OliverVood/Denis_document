<?php

	namespace Base\Templates\HTML\Element;

	use Base\Templates\View;

	class Select extends View {

		public function ToVar(string $name, string $value = '', array $data = [], array $params = []): string {
			$this->Start();
			$this->Render($name, $value, $data, $params);
			return $this->Read();
		}

		public function Render(string $name, string $value = '', array $data = [], array $params = []) { ?>
			<label>
				<select name = "<?= $name; ?>">
					<?php foreach ($data as $key => $text) { ?>
							<option value = "<?= $key; ?>"<?= ($key == $value) ? 'selected' : '' ?>><?= $text; ?></option>
					<?php } ?>
				</select>
			</label>
		<?php }

	}