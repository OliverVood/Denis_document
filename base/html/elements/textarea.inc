<?php

	namespace Base\Templates\HTML\Element;

	use Base\Templates\View;

	class Textarea extends View {

		public function ToVar(string $name, string $value = '', array $params = []): string {
			$this->Start();
			$this->Render($name, $value, $params);
			return $this->Read();
		}

		public function Render(string $name, string $value = '', array $params = []) { ?>
			<label>
				<textarea name = "<?= $name; ?>"><?= $value; ?></textarea>
			</label>
		<?php }

	}