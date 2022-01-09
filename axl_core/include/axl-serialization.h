namespace axl {
	struct serializable_object {
		virtual void std::string serialize() = 0;
		virtual void deserialize(std::string data) = 0;
	};
}