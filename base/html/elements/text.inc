<?php

	namespace Base\Templates\HTML\Element;

	use Base\Templates\View;

	class Text extends View {

		public function ToVar(string $name, string $value = '', array $params = []): string {
			$this->Start();
			$this->Render($name, $value, $params);
			return $this->Read();
		}

		public function Render(string $name, string $value = '', array $params = []) {
			$type = $params['type'] ?? 'text';
		?>
			<input type = "<?= $type; ?>" name = "<?= $name; ?>" value = "<?= $value; ?>">
		<?php }

	}