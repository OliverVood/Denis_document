<?php

	namespace Base\Templates\HTML\Element;

	use Base\Templates\View;

	class File extends View {

		public function ToVar(string $name, string $value = '', array $params = []): string {
			$this->Start();
			$this->Render($name, $value, $params);
			return $this->Read();
		}

		public function Render(string $name, string $value = '', array $params = []) {
			$accept = isset($params['accept']) ? ' accept = "' . $params['accept'] . '"' : '';
		?>
			<input type = "file" name = "<?= $name; ?>" value = "<?= $value; ?>"<?= $accept; ?>>
		<?php }

	}